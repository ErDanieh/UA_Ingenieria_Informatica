# Webapp-Project

## 0. Miembros:
	* Laura Monroig Alemany 48785175J
	* Ander Dorado Bolé 48827596E
	* Julia De La Cruz García 53248743V
	* Sergio Puig Garcia 48773888L
	* Alejandro Ayelo Hernandez 20097543M
	* Daniel Asensi Roch 48776120C

## 1. Descripción:
	Realizaremos la gestión de un cine, donde el usuario podrá visualizar las películas en cartelera,
	ver horarios y reservar entradas de asientos concretos, a su vez podrá comprobar los actores que 
	participan en cada una de ellas así como su director etc.
	
## 2. Parte pública:
	-Mostrar Película-> Mostrará todas las películas disponibles actualmente
	-Mostrar Horarios-> Mostrará los horarios disponibles para cada Película
	-Mostrar Sala-> Mostrará las salas disponibles para cada película
	-Mostrar asientos-> Mostrará los asientos disponibles y no por sala
	-Mostrar próximos estrenos-> Mostrará los próximos estrenos
	-Mostrar precios -> Mostrará los precios de los pases
	-Buscar películas-> Buscador de película deseada

## 3. Listado EN Pública:
	-ENPelicula-> Nombre, Descripción, duración, Reparto, salas, horarios, miniatura, (trailer)
	-ENGenero-> Genero
	-ENIntegrante-> Nombre, tipo
	-ENSala-> ID Sala, asientos, disponibles, película.
	-ENAsiento-> ID, sala, disponibilidad, tipo
	-ENLogin-> Loggea usuario
	-ENRegister-> Registra usuario
	-ENSesion -> Sala, horario, asientos, pelicula
	-ENHorario -> Fecha, Hora, Día, Sala, Película
	
## 4. Listado CAD Pública:
	-CADPelicula-> Nombre, Descripción, duración, Reparto, salas, horarios, miniatura, (trailer)
	-CADGenero-> Genero
	-CADIntegrante-> Nombre, tipo
	-CADSala-> ID Sala, asientos, disponibles, película.
	-CADAsiento-> ID, sala, disponibilidad, tipo
	-CADLogin-> Loggea usuario
	-CADRegister-> Registra usuario
	-CADescuento -> Rango edades, porcentaje descuento
	-CADSesion -> Sala, horario, asientos, pelicula

## 5. Parte privada:
	-Comprar entradas-> Comprar entrada para una película
	-Seleccionar horario-> seleccionar horario de película
	-Seleccionar asiento-> seleccionar asiento disponible para la película
	-Descargar entrada-> El usuario podrá una vez comprada la entrada descargarla
	-Ver Historial de visualización-> El usuario podrá ver las compras realizadas
	-Películas pendientes-> El usuario podrá añadir las películas a sus lista de títulos pendientes
	
## 6. Listado EN Privada:
	-ENAdministrador-> Asignará películas a salas y horarios, eliminará usuarios, añadir películas
	-ENUsuario-> Información del usuario.
	-ENComprar-> Administra la compra de una entrada
	-ENTicket-> Generará un ticket único
	-ENDescuento -> Rango edades, porcentaje descuento
	
## 7. Listado CAD Privada:
	-CADAdministrador-> Asignará películas a salas y horarios, eliminará usuarios, añadir películas
	-CADUsuario-> Información del usuario.
	-CADComprar-> Administra la compra de una entrada
	-CADPendientes-> Añadir película a lista de pendientes
	-CADTicket-> Generará un ticket único

## 8. Posibles mejoras:
	-Redes Sociales
	-Packs de comida
	-Packs de películas
	-Bonos de película
	-Parking
	-Mostrar el tráiler
	-Valoracion
	
## 9. Esquema BB.DD.:
	-Nombre del fichero: esquemaBD.pdf
	-Ubicación: Webapp-Project/master/esquemaBD.pdf
	
## 10. Credenciales Página Web:
	-Usuario normal:
		-Email: ander2@email.com
		-Password: ander1234
	-Usuario Administrador:
		- Email: ander@email.com
		- Password: ander1234
	-Tarjeta de crédito:
		- 1234-1234-1234-1234
		- 123
	-Peliculas con sesión: Interestellar, El Club de la Lucha
	-Formato Fecha: dd/mm/yyyy
	
## 11. Cambios con el proyecto inicial:
	-Debido a diversas complicaciones no hemos podido completar la parte de integrantes (actores, directores)
	-La funcionalidad de reserva de asientos no funciona correctamente puesto que te permite comprar sin reservar 
	asientos y no guarda los asientos que se han comprado.
	-Cuando te registras y compras te mandamos un correo con la información del usuario o con la entrada adjunta
	-Seguridad en las contraseñas y validación de todos los datos
	-QR como entrada
	-Ajustes de usuario
	
## 12. Dificultades:
	-Problemas de falta de actitud
	-Procastinación y entrega incompleta del trabajo individual, sin conexión, provocando que otros miembros 
	tengan que hacer partes que no les corresponden en el último momento
