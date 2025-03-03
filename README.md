# Minishell-42
# Empezando a comprender lo que se debe hacer

A continuación se describe brevemente el funcionamiento del shell cuando lee y ejecuta un comando. Básicamente, el shell hace lo siguiente
*******************************************************************************************************************************************

1) Lee su entrada desde un archivo (ver Scripts de Shell), desde una cadena suministrada como argumento a la opción de invocación -c (ver Invocando Bash), o desde la terminal del usuario.

2) Divide la entrada en palabras y operadores, obedeciendo las reglas de entrecomillado descritas en Entrecomillado. Estos tokens están separados por metacaracteres. La expansión de alias se realiza en este paso (ver Aliases).

3) Convierte los tokens en comandos simples y compuestos (véase Comandos del shell).

4) Realiza las distintas expansiones del intérprete de comandos (consulte Expansiones del intérprete de comandos), dividiendo los tokens expandidos en listas de nombres de archivo (consulte Expansión de nombres de archivo) y comandos y argumentos.

5) Realiza las redirecciones necesarias (ver Redirecciones) y elimina los operadores de redirección y sus operandos de la lista de argumentos.

6) Ejecuta el comando (consulte Ejecución de comandos).

7) Opcionalmente, espera a que el comando finalice y recoge su estado de salida (consulte Estado de salida).

Enlaces y documentacion para revisar: https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation


# Minishell debe: 
*****************************************************
Mostrar una entrada mientras espera un comando nuevo.

Tener un historial funcional.

Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el uso de rutas relativas o absolutas).

Evita utilizar más de una variable global para indicar la recepción de una señal. Piensa en lo que implica: Esta aproximación evita que tu gestor de señales acceda a tus estructuras de datos principales.

No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como \ (barra invertida) o ; (punto y coma).

Gestionar que la ’ evite que el shell interprete los metacaracteres en la secuencia entrecomillada.

Gestionar que la " evite que el shell interprete los metacaracteres en la secuencia entrecomillada exceptuando $ (signo de dólar).

Implementar redirecciones:
< debe redirigir input.
> debe redirigir output.
<< debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca. Sin embargo, no necesita actualizar el historial.
>> debe redirigir el output en modo append.

Implementar pipes (carácter |). El output de cada comando en la pipeline se conecta a través de un pipe al input del siguiente comando.

Gestionar las variables de entorno ($ seguidos de caracteres) que deberán expandirse a sus valores.

Gestionar $?, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.

Gestionar ctrl-C ctrl-D ctrl-\, que deberán funcionar como en bash.

Cuando sea interactivo:
ctrl-C imprime una nueva entrada en una línea nueva.
ctrl-D termina el shell.
ctrl-\ no hace nada.

# Deberá implementar los built-ins:
*****************************************
echo con la opción -n.

cd solo con una ruta relativa o absoluta.

pwd sin opciones.

export sin opciones.

unset sin opciones.

env sin opciones o argumentos.

exit sin opciones.
*************************************************************************************************************************************************


# Proceso
*************************************************************************************************


Recomendamos leer el manual de bash (https://www.gnu.org/software/bash/manual/html_node/index.html)  y dividir el proyecto en fases tal y como se menciona en la sección shell operation (https://www.gnu.org/software/bash/manual/html_node/Shell-Operation.html)

Lee su entrada de un archivo (ver Shell Scripts), de una cadena suministrada como argumento a la opción de invocación -c (ver Invocando Bash), o de la terminal del usuario.

Divide la entrada en palabras y operadores, obedeciendo las reglas de entrecomillado descritas en Entrecomillado. Estos tokens están separados por metacaracteres. 

La expansión de alias se realiza en este paso (ver Aliases). Convierte los tokens en comandos simples y compuestos (véase Comandos del shell).

Realiza las distintas expansiones del intérprete de comandos (consulte Expansiones del intérprete de comandos), dividiendo los tokens expandidos en listas de nombres de archivo (consulte Expansión de nombres de archivo) y comandos y argumentos. 

Realiza las redirecciones necesarias (ver Redirecciones) y elimina los operadores de redirección y sus operandos de la lista de argumentos. 

Ejecuta el comando (consulte Ejecución de comandos). 

Opcionalmente, espera a que el comando finalice y recoge su estado de salida (consulte Estado de salida).


![193665518-0c0c7fec-38a9-4f6c-91ca-fef606abfb0d](https://github.com/user-attachments/assets/080ed608-980c-4c97-875b-f51d5f63b6dd)

# Lectura del input
Utilizamos la libreria readline de GNU que ya está permitido su uso. ver manual: https://tiswww.case.edu/php/chet/readline/rltop.html
Esta libreria, a su vez, nos proporciona el historial que solicita la consigna.

# Análisis lexicológico
Esta etapa consiste en identificar tokens. Leemos caracter a caracter la línea que obtuvimos en el paso anterior y guardamos en una estructura clasificando en word o token siguiendo las reglas de encomillado de bash.

# Análisis sintáctico
La lista de nodos generada por el paso anterior se libera y se generan nuevos nodos para la instancia de ejecución. Aquí también, revisamos si hay redirecciones y generamos los file descriptors para cada uno de los procesos que vayamos a ejecutar más adelante. Cada nodo que generemos es el conjunto de word y token hasta llegar a un PIPE en caso de encontrar uno.

# Expansiones
Antes de enviar la lista de nodos al ejecutor hay que realizar las expansiones necesarias de acuerdo a las reglas de encomillado de bash.

# Redirecciones y liberación de memoria
Una vez hecho el fork() libramos todas las estructuras en memoria del proceso hijo y duplicamos los file descriptors en caso de haber redirecciones.

# Ejecución
Por último, ejecutamos uno a uno todos los nodos que generamos, liberamos memoria, cerramos file descriptors y lanzamos el prompt esperando la nueva secuencia a ejecutar.

*****************************************************************

# Mas informacion de los procesos a realizar

Implementación

El programa se ejecuta sin argumentos (y arrojará un error si se utiliza alguno). El programa consta esencialmente de dos funciones que se llaman entre sí indefinidamente. La primera minishell_loop realiza las funciones de minishell, la otra limpia y prepara la siguiente línea. En minishell_loop, aparece un símbolo del sistema, que se implementa a través de readline . Esto también nos permitió usar la función history incorporada. Una vez que se ha ingresado una línea, verifica si hay comillas sin cerrar. Si no encuentra ninguna, envía la línea al analizador léxico.

El analizador léxico

El analizador léxico, también llamado tokenizador, toma como entrada la línea ingresada. Luego lee la línea palabra por palabra, utilizando espacios en blanco como delimitadores. Primero verifica si la palabra es un token o no, es decir: |, <, <<, >, o >>, y en caso contrario asume que es una palabra. Luego la agrega a la siguiente lista enlazada:

	typedef struct s_lexer
	{
		char    	*str;
 		t_tokens        token;
 		int		i;
 		struct s_lexer	*next;
 		struct s_lexer	*prev;
  	}			t_lexer; 


Cada nodo contiene un char *que contiene la palabra o un t_token. También asignamos a cada nodo un índice para que podamos eliminarlos fácilmente más tarde.

# El analizador

Luego, el analizador léxico se envía al analizador, que agrupa los distintos nodos en función de los tokens. Cada grupo se convierte en un comando.

	typedef struct s_simple_cmds
	{
		char                    **str;
 		int                     (*builtin)(t_tools *, struct s_simple_cmds *);
 		int                     num_redirections;
 		char                    *hd_file_name;
 		t_lexer                 *redirections;
 		struct s_simple_cmds	*next;
		struct s_simple_cmds	*prev;
	}				t_simple_cmds;

![194295673-3c9e17c3-d5ab-40dc-82ef-72b909f4acb3](https://github.com/user-attachments/assets/2dd5b9e8-41a0-47d5-8b1a-c7e3e522b2d5)

Lo primero que hace el analizador es recorrer la lista del analizador léxico hasta que encuentra una tubería (pipe). Luego, toma todos los nodos anteriores a la tubería como un solo comando y crea un nodo en la t_simple_cmds estructura. Si no encuentra una tubería, toma todos los nodos (restantes) como un solo comando.

analizador 001 El analizador toma la t_lexer lista (izquierda) y la convierte en la t_simple_cmds lista (derecha)

Para cada comando, primero comprueba si hay redirecciones, que almacena en la *redirections lista enlazada, que contiene tanto el token como el nombre de archivo o delimitador en el caso de un documento heredado. Cuando se añaden los nodos a la *redirections lista, se eliminan de la lista del analizador léxico. A continuación, comprueba si la primera palabra es una función incorporada, en cuyo caso almacena un puntero de función a la función correspondiente, más sobre esto a continuación. Como las redirecciones se han eliminado de la lista del analizador léxico, el analizador puede combinar fácilmente todas las palabras restantes en una matriz 2D, que es un argumento ejecutivo obligatorio. También facilita el manejo de situaciones en las que las palabras pueden estar separadas por redirecciones, por ejemplo:

cat > file -e
Como > y file ya se eliminaron de la lista del analizador léxico cuando se agregaron a la lista de redirecciones, todo lo que queda es cat y -e, que luego se pueden agregar fácilmente a una matriz.

Este proceso se repite hasta el final de la lista del analizador léxico.

# Elementos incorporados
Como se explicó anteriormente, manejamos las funciones incorporadas almacenando un puntero de función en el t_simple_cmds. Esto lo logramos enviando la primera palabra de un comando a una función builtin_arr que recorre una matriz estática de las diferentes funciones incorporadas. Si encuentra una función correspondiente, la devuelve al analizador; de lo contrario, devuelve NULL. Para mí, esta fue una forma de aprender sobre punteros de función, con los que nunca había trabajado antes. Además, al determinar la función incorporada en la etapa del analizador, simplifica enormemente el ejecutor, ya que ejecutar la función incorporada requiere solo dos líneas de código:

	if (cmd->builtin != NULL)
  		cmd->builtin(tools, cmd);
  
# Las funciones incorporadas (según el tema) son:
** cd	
	Cambia el directorio de trabajo del entorno de ejecución del shell actual y actualiza las variables de entorno PWDy OLDPWD.
  	Sin argumentos, cambia el directorio de trabajo al directorio de inicio.
  	-cambia el directorio al OLDPWD.

** echo	
	Muestra una línea de texto.
  	Bandera opcional -n: no mostrar la nueva línea final.

** env	
	Muestra las variables de entorno

** exit	
	Finaliza el shell.
  	Acepta el argumento opcional n, que establece el estado de salida en n.

** export
	Acepta argumentos name[=value].
	Agrega nombre al entorno. Establece el valor de nombre en value.
  	Si no se proporciona ningún argumento, muestra una lista de variables exportadas.

** pwd	
	Muestra el directorio actual como una ruta absoluta.

** unset
	Acepta el argumento name.
  	Elimina la variable name del entorno.

# Ejecutor
Cuando el analizador devuelve la t_simple_cmds lista a minishell_loop, se realiza una comprobación sencilla para determinar cuántos comandos hay, ya que son manejados por diferentes funciones. Sin embargo, con la excepción de unas pocas funciones integradas, los comandos son ejecutados en última instancia por la misma función handle_cmd, que encuentra y, si tiene éxito, ejecuta el comando.

# Expansor
Antes de que se maneje un nodo t_simple_cmds, se lo expande. El expansor toma las variables, identificadas por $, y las reemplaza con su valor de las variables de entorno. De modo que $USERse convierte en mgraaf, y $? se reemplaza con el código de salida.

# Heredoc
Antes de crear un proceso secundario, el proceso principal ejecuta heredocs. Nosotros manejamos heredocs creando un archivo temporal para escribir la entrada. El nombre del archivo se almacena en el t_simple_cmds nodo relacionado para que pueda usarse para reemplazar STDIN. Si hay varios heredocs en un solo t_simple_cmds nodo, entonces el nombre del archivo que se almacena finalmente será el del último heredoc. El uso de un archivo tiene limitaciones y problemas de seguridad, sin embargo, sentimos que era la forma más simple de lidiar con esto y es similar a cómo lo hace bash.

# Comando único
Al igual que en bash, los comandos integrados, específicamente cd, exit, export, y unsetno se pueden ejecutar en un proceso separado, ya que entonces la variable ambiental no se puede alterar adecuadamente. Si solo hay un comando, y es uno de los comandos integrados mencionados anteriormente, se ejecuta en el proceso padre y la función regresa a minishell_loop. Si el comando no es un comando integrado, la función de comando único crea un nuevo proceso y envía el comando a handle_cmd.

Comandos múltiples
Si hay varios comandos, el ejecutor recorre cada t_simple_cmdsnodo y crea un proceso secundario para él mediante fork(), y mediante pipe()crea una tubería para enviar la salida de un comando como entrada al siguiente. Consulta pipex para obtener más información sobre estas funciones.

Básicamente para cada comando sucede lo siguiente:

El comando se expande.
Se crea una tubería(pipe) con end[0]y end[1], excepto el último comando.
Se crea un proceso secundario fork(). En el proceso secundario:
Con excepción del primer comando, dup2 reemplaza STDINcon la salida del comando anterior.
Con excepción del último comando, dup2 reemplaza STDOUTcon end[1].
En el caso de redirecciones, el STDINo STDOUTse reemplaza con sus respectivos descriptores de archivo.
handle_cmdEncuentra y ejecuta el comando.
end[0]se almacena para el siguiente comando.
Luego, el proceso padre espera a que todos los hijos finalicen y luego regresa al minishell_loop.

# Reiniciar
Luego, el programa realiza un reinicio completo, liberando todos los nodos que aún no han sido liberados o eliminados, y restablece varias variables para que el programa pueda comenzar nuevamente mostrando un nuevo mensaje.

*********************************************************************************************

# Uso
Clona el repositorio
	git clone ... minishell
Compila el proyecto con make
	make
Como se menciona anteriormente, este proyecto requiere de la libreria readline. En caso de no tenerla instalada ejecuta:

En sistemas basados en Debian/Ubuntu:
	sudo apt-get update
	sudo apt-get install libreadline-dev

En sistemas basados en Red Hat/Fedora:
	sudo yum install readline-devel

En macOS (usando Homebrew):
	brew install readline
Ejecuta la minishel
	./minishell

# Mapa mental (todo lo anterior en imagen)

![144017004-aa68e8d7-5da7-4ece-afc6-b8ab100113df](https://github.com/user-attachments/assets/f0e748f6-9d5b-4637-950f-96f77d8c2cc2)

![144017016-ef2bb606-c301-42c6-88f1-8ed4339d22cd](https://github.com/user-attachments/assets/99b3e6da-9ef2-4af4-ba13-98c1e18f5232)

# Documentación
***************************************
BASH manual https://www.academia.edu/33910321/Manual_0_6_MAS_COMPLEO_BASH

GNU readline https://tiswww.case.edu/php/chet/readline/rltop.html

Para consultar las funciones necesarias y sus librerias para importar en minishell.h https://man7.org/linux/man-pages/dir_section_3.html

Documentacion estructura minishell: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

# Copiado e inspirado este pedazo de tutorial, de dos grandes entre otros:
Autores
@Fefeco
@Daviichii89

# Más resources
https://github.com/karisti/42_minishell?tab=readme-ov-file#resources
Para probar con dos terminales y probar bash y tu propia minishell ya que clona el teclado: https://42born2code.slack.com/files/U06D4LACZHA/F07SUS94QMR/init_test.sh 

# Detallando el uso de nuestro propio heredoc
1. ¿Qué es un heredoc?
En Bash, un heredoc te permite escribir un bloque de texto (varias líneas) que se usará como entrada estándar de un comando.
Por ejemplo, si ejecutas en la terminal:

bash
Copiar
Editar
cat <<EOF
Hola, mundo
Esta es una prueba
EOF
Esto hace que el comando cat lea el texto:

Copiar
Editar
Hola, mundo
Esta es una prueba
en lugar de leer desde el teclado. El delimitador EOF le indica al intérprete cuándo terminar de leer el bloque.

2. ¿Cómo se recrea esto en el código?
El código que nos has compartido implementa el heredoc de la siguiente manera:

Crear un archivo temporal donde se almacenarán las líneas ingresadas por el usuario.
Forkear un proceso hijo que se encargue de leer la entrada del usuario línea a línea, hasta encontrar el delimitador (por ejemplo, EOF).
Escribir cada línea en el archivo temporal.
Una vez terminado, el proceso padre abre ese archivo en modo lectura y lo usa para redirigir la entrada estándar del comando.
A continuación, veamos cada parte importante del proceso.

3. Funciones Clave y su Funcionalidad
a) hdoc_redir
Esta es la función principal para configurar el heredoc.
¿Qué hace?

Ignora señales:

c
Copiar
Editar
signal(SIGINT, SIG_IGN);
signal(SIGQUIT, SIG_IGN);
Esto evita que se interrumpa el proceso mientras se configura el heredoc.

Crea un nodo de redirección (t_redir):
Se reserva memoria para almacenar la información del heredoc y se marca que se trata de un heredoc con redir_node->here_doc = 1.

Genera un nombre de archivo temporal:

c
Copiar
Editar
redir_node->filename = ft_random_filename();
Esto crea un nombre aleatorio (por ejemplo, en /tmp) para guardar el contenido del heredoc.

Lanza un proceso hijo:
Llama a la función ft_fork_hdoc que se encarga de crear un proceso hijo para leer la entrada del usuario. Si ocurre algún error (o se recibe una señal de interrupción), se llama a hdoc_error_handler para limpiar recursos.

Abre el archivo temporal para lectura:
Una vez que el hijo termina de escribir, se abre el archivo para que el comando principal (por ejemplo, cat) pueda leerlo como entrada.

b) ft_fork_hdoc
Esta función crea un proceso hijo mediante fork().

Preparación del delimitador ("stop"):
Se toma el token siguiente al operador heredoc para saber cuál es la cadena que indica el final (por ejemplo, EOF). Además, se le eliminan posibles comillas con ft_remove_quotes.

En el proceso hijo (cuando pid == 0):
Se llama a ft_child_hdoc, que se encargará de leer la entrada del usuario.

En el proceso padre:
Se espera a que el hijo termine usando ft_wait_for_childs y, si corresponde, se realiza una expansión de variables (con ft_exp_hd).

c) ft_child_hdoc
Esta función se ejecuta en el proceso hijo y es donde se lleva a cabo la lectura del heredoc.

Restablece las señales:

c
Copiar
Editar
signal(SIGINT, SIG_DFL);
signal(SIGQUIT, SIG_IGN);
Así, el usuario puede usar Ctrl-C (SIGINT) para interrumpir la lectura, mientras que SIGQUIT sigue ignorándose.

Prepara el delimitador:
Se extrae el delimitador (por ejemplo, EOF) del lexer:

c
Copiar
Editar
stop = ft_strdup((*lexer_nodes)->next->value);
Llama a la función de lectura:
Se invoca ft_read_to_file(stop, cmds_amount, f_name), que es la función que:

Abre el archivo temporal.
Lee líneas del usuario con readline("> ").
Escribe cada línea en el archivo hasta que la línea leída sea exactamente igual al delimitador.
Finaliza el proceso:
Si todo sale bien, el hijo hace exit(EXIT_SUCCESS), o si ocurre algún error, termina con exit(EXIT_FAILURE).

d) ft_read_to_file y read_and_write
Estas funciones se encargan de leer y escribir:

Abrir el archivo temporal:
Se abre con las opciones O_CREAT | O_TRUNC para crear o truncar (vaciar) el archivo, de modo que esté listo para escribir.

Bucle de lectura (read_and_write):
Se muestra un prompt ("> ") y se lee la entrada del usuario línea por línea.

Cada línea se compara con el delimitador (stop).
Si la línea es igual a stop, se detiene el bucle.
Si no, la línea se escribe en el archivo temporal (usando write_on_file).
Manejo de Ctrl-D:
Si readline devuelve NULL (por ejemplo, al presionar Ctrl-D), se llama a handle_error_ctrl_d para gestionar el error.
Escribir en el archivo (write_on_file):
Se escribe la línea y se añade un salto de línea. Si ocurre algún error al escribir, se retorna -1 para detener el proceso.

e) Funciones de manejo de errores
check_file:
Después de haber creado el archivo, esta función se puede usar para verificar que el archivo existe y es legible. Utiliza access() con los flags F_OK y R_OK y, en caso de error, imprime un mensaje.

hdoc_error_handler y exit_redir:
Si ocurre algún error en el proceso del heredoc (por ejemplo, error al forkear o escribir en el archivo), estas funciones se encargan de:

Eliminar el archivo temporal (con unlink).
Liberar la memoria asignada.
Ajustar el estado de error en la estructura del comando (parser_nodes->error_fd).
4. Ejemplo Práctico: Recreando un heredoc
Imagina que en tu minishell escribes:

bash
Copiar
Editar
cat <<EOF
Hola, mundo
Esta es una prueba
EOF
El proceso sería el siguiente:

Detección del heredoc:
El lexer identifica el operador << y toma EOF como delimitador.

Configuración del heredoc (hdoc_redir):

Se ignoran las señales para evitar interrupciones.
Se crea un nodo de redirección y se asigna un nombre de archivo temporal, por ejemplo, /tmp/tmp12345.
Fork y lectura (ft_fork_hdoc y ft_child_hdoc):

Se crea un proceso hijo.
En el hijo, se establece el delimitador EOF y se llama a ft_read_to_file.
Se muestra el prompt > y el usuario escribe:
Copiar
Editar
Hola, mundo
El texto se escribe en /tmp/tmp12345.
Se vuelve a mostrar el prompt > y el usuario escribe:
nginx
Copiar
Editar
Esta es una prueba
También se escribe en el archivo.
Al ingresar EOF, la función detecta que es el delimitador y se detiene la lectura.
Finalización y uso del heredoc:

El proceso hijo termina y el proceso padre espera su finalización.
El archivo /tmp/tmp12345 se abre en modo lectura.
Cuando se ejecuta cat, la entrada estándar se redirige a este archivo, y el contenido:
Copiar
Editar
Hola, mundo
Esta es una prueba
se muestra en pantalla.
Limpieza:
Una vez usado, se liberan los recursos y se puede eliminar el archivo temporal si ya no es necesario.

5. Resumen del Flujo General
Detección: Se detecta la presencia de un heredoc en el comando.
Preparación: Se crea un archivo temporal y se configura un nodo de redirección.
Fork y Lectura:
Se forkea un proceso hijo.
El hijo lee líneas del usuario hasta encontrar el delimitador.
Cada línea se escribe en el archivo temporal.
Uso: El proceso padre abre el archivo y lo utiliza para redirigir la entrada estándar del comando.
Manejo de Errores y Limpieza: Si ocurre algún error, se limpian los recursos y se informa del fallo.

# Uso de Valgrind en el programa (sube el archivo <readline.ignore> para probar los leaks sin los errores de readline 
 valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all  --trace-children=yes --track-origins=yes --suppressions=readline.ignore -q ./minishell

 #Hoja de evaluación básica 
[ https://github.com/rizky/42-corrections/blob/master/minishell.pdf](https://github.com/mharriso/school21-checklists/blob/master/ng_3_minishell.pdf)
