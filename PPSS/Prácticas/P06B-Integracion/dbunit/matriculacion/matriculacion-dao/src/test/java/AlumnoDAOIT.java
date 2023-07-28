import org.dbunit.Assertion;
import org.dbunit.IDatabaseTester;
import org.dbunit.database.IDatabaseConnection;
import org.dbunit.dataset.FilteredDataSet;
import org.dbunit.dataset.IDataSet;
import org.dbunit.dataset.ITable;
import org.dbunit.util.fileloader.FlatXmlDataFileLoader;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import ppss.matriculacion.dao.DAOException;
import ppss.matriculacion.dao.FactoriaDAO;
import ppss.matriculacion.dao.IAlumnoDAO;
import ppss.matriculacion.to.AlumnoTO;

import java.time.LocalDate;
import java.time.Month;

import static org.junit.jupiter.api.Assertions.*;


public class AlumnoDAOIT {

    IAlumnoDAO alumnoDAO;
    private  IDatabaseTester databaseTester;
    private IDatabaseConnection connection;

    private IDataSet databaseDataSet;


    @BeforeEach
    void setUp() throws Exception {
        //Inicializamos la conexion con la BBDD
        String cadena_conexionDB = "jdbc:mysql://localhost:3306/matriculacion?allowPublicKeyRetrieval=true&useSSL=false";
        databaseTester = new MiJdbceDatabaseTester("com.mysql.cj.jdbc.Driver",
                cadena_conexionDB, "root", "ppss");
        //obtenemos la conexión con la BD
        connection = databaseTester.getConnection();
        //Creamos la factoria de alumnos y obtenemos un alumno
        alumnoDAO = new FactoriaDAO().getAlumnoDAO();

        //Inicializamos el dataSet con los datos iniciales de la tabla cliente
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        //Inyectamos el dataset en el objeto databaseTester
        databaseTester.setDataSet(dataSet);
        //inicializamos la base de datos con los contenidos del dataset
        databaseTester.onSetup();
    }

    @Test
    void testA1() throws Exception{
        AlumnoTO p = new AlumnoTO();
        p.setNif("33333333C");
        p.setNombre("Elena Aguirre Juarez");
        p.setFechaNacimiento(LocalDate.of(1985,02,22));


        //invocamos a nuestro SUT
        Assertions.assertDoesNotThrow(()->alumnoDAO.addAlumno(p));

        //recuperamos los datos de la BD después de invocar al SUT
        IDataSet databaseDataSet = connection.createDataSet();
        //Recuperamos los datos de la tabla cliente
        ITable actualTable = databaseDataSet.getTable("alumnos");

        //creamos el dataset con el resultado esperado
        IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/tabla3.xml");
        ITable expectedTable = expectedDataSet.getTable("alumnos");

        Assertion.assertEquals(expectedTable, actualTable);

    }

    @Test
    void testA2() throws Exception{
        String excepcionEsperada = "Error al conectar con BD";
        AlumnoTO alumno = new AlumnoTO();
        alumno.setNif("11111111A");
        alumno.setNombre("Alfonso Ramirez Ruiz");
        alumno.setFechaNacimiento(LocalDate.of(1982, Month.FEBRUARY, 22));

        DAOException exceptionLanzada = assertThrows(DAOException.class, ()->alumnoDAO.addAlumno(alumno));
        Assertions.assertEquals(excepcionEsperada, exceptionLanzada.getMessage());

    }

    @Test
    void testA3() throws Exception{
        String excepcionEsperada = "Error al conectar con BD";
        AlumnoTO alumno = new AlumnoTO();
        alumno.setNif("44444444D");
        alumno.setNombre(null);
        alumno.setFechaNacimiento(LocalDate.of(1982, Month.FEBRUARY, 22));

        DAOException exceptionLanzada = assertThrows(DAOException.class, ()->alumnoDAO.addAlumno(alumno));
        Assertions.assertEquals(excepcionEsperada, exceptionLanzada.getMessage());

    }

    @Test
    void testA4() throws Exception{
        AlumnoTO alumno = null;
        String excepcionEsperada = "Alumno nulo";

        DAOException excepcionReal = assertThrows(DAOException.class, ()-> alumnoDAO.addAlumno(alumno));
        Assertions.assertEquals(excepcionEsperada, excepcionReal.getMessage());
    }


    @Test
    void testA5() {
        String excepcionEsperada = "Error al conectar con BD";
        AlumnoTO alumno = new AlumnoTO();
        alumno.setNif(null);
        alumno.setNombre("Pedro Garcia Lopez");
        alumno.setFechaNacimiento(LocalDate.of(1982, Month.FEBRUARY, 22));

        DAOException excepcionReal = assertThrows(DAOException.class, () -> alumnoDAO.addAlumno(alumno));

        Assertions.assertEquals(excepcionEsperada, excepcionReal.getMessage());
    }

    @Test
    void testB1() throws Exception{


        Assertions.assertDoesNotThrow(()->alumnoDAO.delAlumno("11111111A"));


        //recuperamos los datos de la BD después de invocar al SUT
        IDataSet databaseDataSet = connection.createDataSet();
        //Recuperamos los datos de la tabla cliente
        ITable actualTable = databaseDataSet.getTable("alumnos");

        //creamos el dataset con el resultado esperado
        IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/tabla4.xml");
        ITable expectedTable = expectedDataSet.getTable("alumnos");

        Assertion.assertEquals(expectedTable, actualTable);


    }

    @Test
    void testB2() throws Exception{
        //invocamos a nuestro SUT
        DAOException exceptionLanzada= Assertions.assertThrows(DAOException.class,()->alumnoDAO.delAlumno("33333333A"));

        assertEquals("No se ha borrado ningun alumno", exceptionLanzada.getMessage());

    }




}
