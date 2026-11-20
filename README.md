# Proyecto_SR38
# ROVINS
## Issue Log — Registro de incidencias y seguimiento técnico

**Versión:** 1.0  
**Fecha de actualización:** 20 de noviembre de 2026  
**Área:** Programación / Arquitectura / Motor 2D  
**Estado:** Registro inicial

---

# 1. Propósito

El Issue Log es el registro central de problemas técnicos, errores, riesgos, refactorizaciones y mejoras identificadas durante el desarrollo de ROVINS.

Su finalidad es:

- Evitar perder problemas detectados durante las sesiones de programación.
- Mantener un historial de correcciones.
- Priorizar las tareas según su impacto.
- Identificar clases y archivos involucrados.
- Evitar corregir varias cosas a la vez sin comprobar resultados.
- Registrar decisiones técnicas para futuras modificaciones.

# 2. Convenciones

## 2.1 Tipos de incidencia

| Tipo | Significado |
|---|---|
| BUG | Error de funcionamiento |
| FIX | Corrección implementada |
| REFACTOR | Mejora estructural del código |
| RISK | Riesgo técnico |
| TASK | Trabajo pendiente |
| DESIGN | Decisión de arquitectura |

## 2.2 Prioridades

| Prioridad | Significado |
|---|---|
| P0 — Crítica | Puede provocar fallos graves o pérdida de estabilidad |
| P1 — Alta | Debe atenderse antes de ampliar funcionalidades relacionadas |
| P2 — Media | Mejora importante, pero no bloquea el desarrollo |
| P3 — Baja | Mejora secundaria |

## 2.3 Estados

- **Abierto:** problema identificado, sin corrección aplicada.
- **En análisis:** requiere investigación.
- **En progreso:** corrección en desarrollo.
- **Pendiente de prueba:** cambio realizado, falta validarlo.
- **Resuelto:** corregido y comprobado.
- **Aceptado:** comportamiento conocido que se conserva intencionalmente.
- **Diferido:** se atenderá en una etapa posterior.

# 3. Registro de incidencias

## ISSUE-001 — Constructor de copia de OpenGLClass

**Tipo:** BUG / REFACTOR  
**Prioridad:** P0  
**Estado:** Pendiente de corrección y prueba  
**Archivos:** `OpenGLClass.h`, `OpenGLClass.cpp`, `Scene.h`

**Descripción:**

`OpenGLClass` administra recursos relacionados con GLFW, incluyendo un puntero a la ventana y un puntero a la entrada.

Se detectó un constructor de copia vacío que no inicializa los miembros. Esto permite situaciones peligrosas cuando el compilador genera operaciones de copia o asignación superficiales.

En `Scene` también existía la asignación:

`gl = OpenGLClass();`

Esta operación podía provocar comportamiento indefinido y problemas durante la destrucción del objeto temporal.

**Corrección propuesta:**

- Eliminar el constructor de copia vacío.
- Prohibir copia y movimiento en `OpenGLClass`.
- Eliminar la asignación temporal del constructor de `Scene`.
- Permitir que `gl` se construya automáticamente como miembro de `Scene`.

**Criterio de aceptación:**

El proyecto compila, inicializa GLFW, abre la ventana y termina sin errores relacionados con la destrucción de objetos.

---

## ISSUE-002 — Propiedad de InputClass

**Tipo:** DESIGN / RISK  
**Prioridad:** P1  
**Estado:** En análisis  
**Archivos:** `Scene.h`, `Scene.cpp`, `OpenGLClass.h`, `OpenGLClass.cpp`

**Descripción:**

`Scene` crea dinámicamente un objeto `InputClass`, pero `OpenGLClass::Shutdown()` también se encarga de eliminarlo.

La propiedad del objeto está distribuida entre dos clases, lo cual dificulta mantener un ciclo de vida seguro.

**Propuesta:**

Establecer una única propietaria.

Diseño preferido:

- `Scene` administra `InputClass` mediante `std::unique_ptr`.
- `OpenGLClass` conserva únicamente un puntero no propietario.
- `OpenGLClass::Shutdown()` deja de eliminar `InputClass`.
- La destrucción del objeto se realiza automáticamente cuando `Scene` termina su ciclo de vida.

**Dependencias:**

Debe modificarse de manera coordinada. No convertir únicamente el puntero de `Scene` sin cambiar la liberación en `OpenGLClass`.

**Criterio de aceptación:**

No existen dobles liberaciones ni accesos a `InputClass` después de su destrucción.

---

## ISSUE-003 — Liberación segura de OpenGLClass

**Tipo:** REFACTOR / RISK  
**Prioridad:** P1  
**Estado:** Abierto  
**Archivos:** `OpenGLClass.cpp`

**Descripción:**

`Shutdown()` destruye la ventana, termina GLFW y elimina el puntero de entrada.

Debe garantizarse que la operación sea segura cuando se invoque más de una vez.

También debe verificarse el comportamiento cuando la inicialización falla parcialmente.

**Correcciones propuestas:**

- Comprobar que `m_window` exista antes de destruirlo.
- Poner los punteros en `nullptr` después de liberarlos.
- Evitar llamadas repetidas innecesarias a `glfwTerminate()`.
- Revisar las rutas de error durante la inicialización de GLFW y GLAD.
- Comprobar que `WindowShouldClose()` gestione correctamente una ventana nula.

**Criterio de aceptación:**

La inicialización, el cierre normal y los fallos de inicialización no producen accesos inválidos ni liberaciones duplicadas.

---

## ISSUE-004 — Copia superficial de clases que administran recursos

**Tipo:** RISK / REFACTOR  
**Prioridad:** P1  
**Estado:** En análisis  
**Archivos:** `Model.h`, `Renderer2D.h`, `Texture2D.h`, `Shader2D.h`

**Descripción:**

Varias clases administran recursos de OpenGL mediante identificadores y punteros.

Una copia superficial podría provocar que dos objetos intenten liberar el mismo recurso.

**Clases identificadas:**

- `Model`
- `Renderer2D`
- `Texture2D`
- `Shader2D`

**Acciones:**

1. Revisar constructores y destructores.
2. Identificar qué recursos posee cada clase.
3. Prohibir copias donde no sean seguras.
4. Evaluar si alguna clase necesita operaciones de movimiento.
5. Evitar liberar dos veces el mismo identificador OpenGL.

**Criterio de aceptación:**

Cada recurso tiene una única responsabilidad de liberación y los objetos no pueden copiarse accidentalmente de manera insegura.

---

## ISSUE-005 — Duplicación de shaders, texturas y geometría en Model

**Tipo:** REFACTOR  
**Prioridad:** P1  
**Estado:** Abierto  
**Archivos:** `Model.h`, `Model.cpp`, `ResourceManager.h`, `ResourceManager.cpp`, `Renderer2D.h`, `Renderer2D.cpp`

**Descripción:**

Actualmente, cada instancia de `Model` puede crear su propio shader, textura y geometría de renderizado.

Esto puede generar duplicación de recursos y un mayor consumo de memoria.

El proyecto ya cuenta con `ResourceManager` y `Renderer2D`, que permiten compartir recursos.

**Objetivo:**

Definir una arquitectura donde las entidades reutilicen recursos compartidos cuando corresponda.

**Acciones:**

- Revisar cómo se construye `Model`.
- Revisar los constructores actuales de `Renderer2D`.
- Verificar la compatibilidad entre `ResourceManager` y `Renderer2D`.
- Determinar qué recursos pertenecen a cada entidad y cuáles son compartidos.
- Evitar reconstruir el sistema antes de comprender las dependencias actuales.

**Criterio de aceptación:**

Los recursos compartibles se cargan una sola vez y las entidades pueden utilizarlos sin administrar copias innecesarias.

---

## ISSUE-006 — Liberación de recursos en ResourceManager

**Tipo:** RISK / REFACTOR  
**Prioridad:** P1  
**Estado:** En análisis  
**Archivos:** `ResourceManager.cpp`, `Shader2D.cpp`, `Texture2D.cpp`, `Game.cpp`

**Descripción:**

`ResourceManager::Clear()` limpia los mapas de recursos y llama explícitamente a `Shader2D::Shutdown()`.

Es necesario comprobar si los destructores también ejecutan `Shutdown()` o liberan los mismos recursos.

También debe garantizarse que los recursos OpenGL se destruyan mientras el contexto siga activo.

**Acciones:**

- Revisar el destructor de `Shader2D`.
- Revisar el destructor de `Texture2D`.
- Revisar el destructor de `Renderer2D`.
- Definir el orden correcto de destrucción.
- Asegurar que `ResourceManager::Clear()` se ejecute antes de destruir el contexto OpenGL.

**Criterio de aceptación:**

Los recursos se liberan una sola vez y antes de destruir el contexto que necesitan.

---

## ISSUE-007 — SetKey ignora el estado recibido

**Tipo:** BUG  
**Prioridad:** P2  
**Estado:** Abierto  
**Archivo:** `InputClass.cpp`

**Descripción:**

El método `SetKey(KeyBoard::Keys key, bool f)` ignora el valor de `f` y asigna siempre `true`.

**Corrección propuesta:**

```cpp
KEYS[key] = f;
```

**Criterio de aceptación:**

El método permite tanto activar como desactivar una tecla.

---

## ISSUE-008 — Lectura del teclado mediante GetKeyboardState

**Tipo:** BUG / RISK  
**Prioridad:** P1  
**Estado:** Abierto  
**Archivo:** `InputClass.cpp`

**Descripción:**

Se detectó una posible inconsistencia al interpretar el estado del teclado.

El código utiliza un arreglo `char` y una máscara `0x8000`, mientras que `GetKeyboardState()` trabaja con valores de tipo `BYTE`.

La máscara debe revisarse porque el bit de estado de tecla presionada se representa mediante `0x80`.

**Acciones:**

- Revisar el tipo del arreglo.
- Verificar el valor devuelto por `GetKeyboardState()`.
- Corregir la interpretación del bit más significativo.
- Probar pulsación y liberación de teclas.

**Criterio de aceptación:**

La detección de teclas funciona correctamente y no depende de conversiones incorrectas de tipos.

---

## ISSUE-009 — Inicialización de arreglos de botones del gamepad

**Tipo:** BUG / RISK  
**Prioridad:** P2  
**Estado:** Abierto  
**Archivo:** `InputClass.cpp`

**Descripción:**

Los arreglos `Btn_XBOX`, `BtnDOWN_XBOX` y `Btn_XBOX_old` requieren una revisión de su inicialización.

También debe verificarse el estado inicial de `m_keyboardState`.

**Acciones:**

- Inicializar todos los estados.
- Revisar los valores por defecto.
- Probar la detección de pulsaciones y liberaciones.
- Verificar el comportamiento cuando no hay gamepad conectado.

**Criterio de aceptación:**

No existen valores indeterminados al iniciar el sistema de entrada.

---

## ISSUE-010 — Dependencia directa de GLFW en Jugador

**Tipo:** REFACTOR  
**Prioridad:** P2  
**Estado:** Diferido  
**Archivos:** `Jugador.cpp`, `InputClass.h`, `InputClass.cpp`, `Scene.cpp`

**Descripción:**

`Jugador::update()` consulta directamente el contexto actual de GLFW y utiliza las teclas W, A, S y D.

Esto acopla el comportamiento del jugador con la biblioteca de ventanas.

El proyecto cuenta con `InputClass`, pero actualmente no existe una integración consolidada entre ambos sistemas.

**Objetivo:**

Desacoplar el movimiento del jugador del mecanismo concreto de entrada.

**Propuesta:**

Crear una interfaz de entrada o un mecanismo centralizado para consultar acciones del juego.

Ejemplos de acciones:

- Mover arriba.
- Mover abajo.
- Mover izquierda.
- Mover derecha.
- Interactuar.
- Abrir menú.

**Criterio de aceptación:**

El jugador recibe información de entrada sin depender directamente de GLFW.

---

## ISSUE-011 — Uso innecesario de dynamic_cast en Scene

**Tipo:** REFACTOR  
**Prioridad:** P3  
**Estado:** Abierto  
**Archivo:** `Scene.cpp`

**Descripción:**

En un bloque de interacción con NPC se utiliza `dynamic_cast` para convertir un objeto obtenido desde una colección de `unique_ptr<PersonajeNpc>`.

La conversión no es necesaria porque el tipo ya está definido por la colección.

**Corrección propuesta:**

Obtener el puntero directamente:

```cpp
PersonajeNpc* npc = it->get();

if (!npc) continue;
```

**Criterio de aceptación:**

La interacción conserva el comportamiento actual y elimina conversiones innecesarias.

---

## ISSUE-012 — Orden del ciclo principal del juego

**Tipo:** REFACTOR / RISK  
**Prioridad:** P2  
**Estado:** Abierto  
**Archivo:** `Game.cpp`

**Descripción:**

El ciclo actual realiza el dibujo antes de actualizar el estado del juego y procesa los eventos de GLFW al final del ciclo.

Se debe evaluar el orden de actualización, entrada, renderizado y presentación.

**Objetivo:**

Establecer un ciclo consistente:

1. Procesar eventos.
2. Actualizar entrada.
3. Actualizar lógica del juego.
4. Renderizar.
5. Intercambiar buffers.

También debe revisarse el control de `deltaTime` para evitar saltos excesivos después de pausas o interrupciones.

**Criterio de aceptación:**

La respuesta de los controles y la actualización visual son consistentes.

---

## ISSUE-013 — Soporte de caracteres UTF-8

**Tipo:** TASK  
**Prioridad:** P2  
**Estado:** Diferido  
**Archivo:** `TextRenderer.h`, `TextRenderer.cpp`

**Descripción:**

El sistema actual utiliza `unsigned char` como clave para almacenar caracteres del atlas.

Esto no permite representar correctamente todos los caracteres UTF-8, incluyendo vocales acentuadas y la letra ñ.

**Objetivo:**

Permitir diálogos en español con todos sus caracteres.

**Acciones futuras:**

- Definir una estrategia de codificación.
- Implementar decodificación UTF-8.
- Ampliar el atlas de caracteres.
- Verificar el renderizado de signos de apertura y cierre.

**Criterio de aceptación:**

El sistema muestra correctamente textos en español, incluyendo tildes, ñ y signos de puntuación.

---

## ISSUE-014 — Limpieza manual de memoria en Scene

**Tipo:** REFACTOR / RISK  
**Prioridad:** P1  
**Estado:** En análisis  
**Archivo:** `Scene.cpp`

**Descripción:**

`Scene::liberarMemoria()` realiza llamadas manuales a métodos de liberación en objetos que también son administrados mediante `std::unique_ptr`.

Debe revisarse si los destructores de esas clases liberan los mismos recursos.

**Objetivo:**

Evitar responsabilidades duplicadas de destrucción.

**Acciones:**

- Revisar destructores de `Jugador`, `PersonajeNpc`, `Terreno` y `Model`.
- Identificar los recursos propios de cada clase.
- Separar la liberación de recursos OpenGL de la destrucción de objetos cuando corresponda.
- Mantener el orden de destrucción compatible con el contexto OpenGL.

**Criterio de aceptación:**

Cada recurso se libera una sola vez y los objetos administrados por `unique_ptr` se destruyen correctamente.

---

## ISSUE-015 — Exceso de responsabilidades en Scene

**Tipo:** REFACTOR / DESIGN  
**Prioridad:** P2  
**Estado:** Diferido  
**Archivo:** `Scene.h`, `Scene.cpp`

**Descripción:**

`Scene` concentra múltiples responsabilidades:

- Inicialización de OpenGL.
- Administración de entidades.
- Movimiento e interacción.
- Colisiones.
- Diálogos.
- Renderizado.
- Administración de entrada.
- Depuración.

Esto puede dificultar el mantenimiento conforme aumente el tamaño del videojuego.

**Objetivo:**

Convertir `Scene` gradualmente en una clase coordinadora.

**Posibles sistemas a extraer:**

- EntityManager.
- CollisionSystem.
- InputHandler.
- DialogueController.
- SceneRenderer.

**Criterio de aceptación:**

Cada sistema tiene responsabilidades definidas y `Scene` conserva la coordinación general sin acumular toda la lógica.

---

## ISSUE-016 — Semántica de CollRect

**Tipo:** DESIGN / REFACTOR  
**Prioridad:** P3  
**Estado:** Abierto  
**Archivo:** `CollRect.h`

**Descripción:**

Los métodos `intersects()`, `overlaps()` y `contains()` utilizan criterios ligeramente distintos para considerar los bordes de los rectángulos.

Debe documentarse y unificarse la semántica según el comportamiento deseado.

**Criterio de aceptación:**

Las colisiones y detecciones de contacto utilizan reglas consistentes y documentadas.

---

## ISSUE-017 — Proyección y uniform de Model::draw

**Tipo:** BUG / REFACTOR  
**Prioridad:** P1  
**Estado:** Abierto  
**Archivo:** `Model.cpp`

**Descripción:**

El método `draw(const glm::mat4& projection)` recibe una matriz de proyección, pero se detectó que el uniform correspondiente se configura en el constructor y no necesariamente se actualiza durante el dibujo.

Esto puede producir resultados incorrectos cuando cambia la cámara o la proyección.

**Acción propuesta:**

Verificar que el shader reciba la matriz actual en cada operación de dibujo, o definir un mecanismo centralizado para actualizarla.

**Criterio de aceptación:**

El renderizado utiliza la proyección vigente y no depende exclusivamente del valor establecido durante la construcción del objeto.

---

# 4. Correcciones confirmadas previamente

## FIX-001 — Orientación del atlas de caracteres

**Estado:** Resuelto  
**Archivo:** `Renderer2D.cpp`

Se corrigió la orientación vertical de las coordenadas UV en `DrawSpriteRegion()` intercambiando los valores correspondientes de `v0` y `v1`.

**Resultado:** El atlas `alfabeto_blanco.png` se muestra con la orientación correcta.

## FIX-002 — Inicialización de geometría en Renderer2D

**Estado:** Resuelto  
**Archivo:** `Renderer2D.cpp`

Se corrigió la condición de inicialización de `initRenderData()`:

```cpp
if (!shaderPtr || quadVAO != 0 || quadVBO != 0) return;
```

**Resultado:** Se evita inicializar la geometría cuando falta el shader o cuando los recursos ya existen.

## FIX-003 — Búsqueda de NPC durante interacción por tecla

**Estado:** Corrección aplicada  
**Archivo:** `Scene.cpp`

Se simplificó el acceso a los NPC mediante `unique_ptr<PersonajeNpc>`, utilizando `npc.get()` en lugar de una conversión dinámica innecesaria.

---

# 5. Orden recomendado de resolución

| Orden | Issue | Prioridad | Motivo |
|---:|---|---|---|
| 1 | ISSUE-001 | P0 | Seguridad de construcción y destrucción |
| 2 | ISSUE-002 | P1 | Propiedad única de InputClass |
| 3 | ISSUE-003 | P1 | Cierre seguro de GLFW |
| 4 | ISSUE-004 | P1 | Seguridad de recursos |
| 5 | ISSUE-006 | P1 | Orden de liberación OpenGL |
| 6 | ISSUE-014 | P1 | Evitar liberaciones duplicadas |
| 7 | ISSUE-005 | P1 | Reutilización de recursos |
| 8 | ISSUE-017 | P1 | Proyección del renderizado |
| 9 | ISSUE-008 | P1 | Lectura correcta del teclado |
| 10 | ISSUE-009 | P2 | Inicialización del gamepad |
| 11 | ISSUE-010 | P2 | Desacoplamiento de entrada |
| 12 | ISSUE-012 | P2 | Ciclo principal |
| 13 | ISSUE-013 | P2 | Caracteres en español |
| 14 | ISSUE-015 | P2 | Organización de Scene |
| 15 | ISSUE-007 | P2 | Corrección de SetKey |
| 16 | ISSUE-011 | P3 | Simplificación de código |
| 17 | ISSUE-016 | P3 | Consistencia de colisiones |

# 6. Reglas de mantenimiento del Issue Log

1. Cada problema nuevo debe recibir un identificador consecutivo.
2. No se marcará como resuelto un problema únicamente porque el código haya sido modificado.
3. Para cerrar un issue debe existir una prueba o comprobación.
4. Los cambios que involucren varios archivos deben registrarse con sus dependencias.
5. Si una modificación genera un problema nuevo, se registra una incidencia independiente.
6. Los issues diferidos deben conservarse hasta que se atiendan o se decida formalmente descartarlos.
7. Los problemas relacionados deben vincularse mediante sus identificadores.
8. Las correcciones confirmadas deben pasar a la sección de historial de soluciones.

# 7. Próxima sesión de programación

**Objetivo:** Continuar la auditoría de arquitectura y propiedad de recursos sin alterar funcionalidades existentes.

Orden de trabajo:

1. Confirmar la aplicación de las modificaciones propuestas para `OpenGLClass`.
2. Compilar y probar la inicialización y el cierre del juego.
3. Revisar `Personaje.h/.cpp`.
4. Confirmar el estado actual de `Terreno.h/.cpp`.
5. Revisar `Shader2D.h/.cpp`.
6. Definir el ciclo de vida de los recursos antes de modificar `Model` o `ResourceManager`.

**Regla principal:** realizar una modificación controlada, compilar, probar y documentar antes de continuar con la siguiente.

---

**Fin del registro inicial.**
