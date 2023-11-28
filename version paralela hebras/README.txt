La version secuencial de la tarea consta de 6 imagenes y el codigo fuente llamado "hebras".
Para poder compilar el programa se utiliza el software CMake, para ello siga los siguientes pasos:

1 Abra el directorio donde esta el programa en su version secuencial con la terminal.
2 Ejecute el siguiente comando:
	nano CMakeLists.txt
3 En el archivo de texto copie las instrucciones:

	cmake_minimum_required(VERSION 2.8)
	project( hebras )
	find_package( OpenCV REQUIRED )
	include_directories( ${OpenCV_INCLUDE_DIRS} )
	add_executable( hebras hebras.cpp )
	target_link_libraries( hebras ${OpenCV_LIBS} )
	
guarde el archivo con el mismo nombre y los cambios realizados

4 Ejecute el siguiente comando:
	cmake .
5 Ejecute la siguiente instrucción:
	make
6 El programa ya se encuentra listo para ser ejecutado, este recibe tres parametros y se ejecuta en la terminal de la siguiente forma:
./hebras nombreImagenAColor nombreImagenEscalaGrises numeroDeHebras 
