package ppss;

import org.dbunit.Assertion;
import org.dbunit.IDatabaseTester;
import org.dbunit.JdbcDatabaseTester;
import org.dbunit.database.IDatabaseConnection;
import org.dbunit.dataset.FilteredDataSet;
import org.dbunit.dataset.IDataSet;
import org.dbunit.dataset.ITable;
import org.dbunit.util.fileloader.FlatXmlDataFileLoader;

import org.junit.jupiter.api.*;

/* IMPORTANTE:
    Dado que prácticamente todos los métodos de dBUnit lanzan una excepción,
    vamos a usar "throws Esception" en los métodos, para que el código quede más
    legible sin necesidad de usar un try..catch o envolver cada sentencia dbUnit 
    con un assertDoesNotThrow()
    Es decir, que vamos a primar la legibilidad de los tests.
    Si la SUT puede lanza una excepción, SIEMPRE usaremos assertDoesNotThrow para
    invocar a la sut cuando no esperemos que se lance dicha excepción (independientemente de que hayamos propagado las excepciones provocadas por dbunit).
*/
public class ClienteDAO_IT {

  private ClienteDAO clienteDAO; //SUT
  private IDatabaseTester databaseTester;
  private IDatabaseConnection connection;

  @BeforeEach
  public void setUp() throws Exception {

    String cadena_conexionDB = "jdbc:mysql://localhost:3306/DBUNIT?allowPublicKeyRetrieval=true&useSSL=false";
    databaseTester = new MiJdbceDatabaseTester("com.mysql.cj.jdbc.Driver", cadena_conexionDB
            , "root", "ppss");
    connection = databaseTester.getConnection();

    //inicializamos la BD
    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-init.xml");
    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    clienteDAO = new ClienteDAO();
  }

  @Test
  public void testInsert() throws Exception {
    Cliente cliente = new Cliente(1,"John", "Smith");
    cliente.setDireccion("1 Main Street");
    cliente.setCiudad("Anycity");


    
     //invocamos a la sut
    Assertions.assertDoesNotThrow(()->clienteDAO.insert(cliente));

    //recuperamos los datos de la BD después de invocar al SUT
    IDataSet databaseDataSet = connection.createDataSet();
    ITable actualTable = databaseDataSet.getTable("cliente"); 

    //creamos el dataset con el resultado esperado
    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-esperado.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);

   }

  @Test
  public void testDelete() throws Exception {
    Cliente cliente =  new Cliente(1,"John", "Smith");
    cliente.setDireccion("Other Street");
    cliente.setCiudad("NewCity");

    //Inicializamos la base de datos
    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-esperado.xml");
    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    //invocamos a la SUT
    Assertions.assertDoesNotThrow(()->clienteDAO.delete(cliente));

    //recuperamos los datos de la BD después de invocar al SUT
    IDataSet databaseDataSet = connection.createDataSet();
    ITable actualTable = databaseDataSet.getTable("cliente");
    
    //creamos el dataset con el resultado esperado
    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-init.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);
  }


  @Test
  public void testInsert2() throws Exception {
    //Definimos el modelo que va a entrar al sql
    Cliente cliente =  new Cliente(1,"John", "Smith");
    cliente.setDireccion("Other Street");
    cliente.setCiudad("NewCity");


    Assertions.assertDoesNotThrow(()->clienteDAO.insert(cliente));

    IDataSet databaseSet = connection.createDataSet();
    ITable actualTable = databaseSet.getTable("cliente");

    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-esperado-apartadoD.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable,actualTable);
  }

  @Test
  public void testDelete2() throws Exception {

    //Definimos el modelo que va a entrar al sql
    Cliente cliente =  new Cliente(1,"John", "Smith");
    cliente.setDireccion("1 Main Street");
    cliente.setCiudad("Anycity");

    //Inicializamos la base de datos
    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-esperado.xml");
    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    //Invocamos a la sut
    Assertions.assertDoesNotThrow(()->clienteDAO.delete(cliente));

    //Recuperamos los datos de la tabla
    IDataSet databaseDataSet = connection.createDataSet();
    ITable actualTable = databaseDataSet.getTable("cliente");

    //Creamos el dataset con el resultado que esperamos
    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-init.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    //Comparamos los dos dataset, el que recuperamos y el que esperamos
    Assertion.assertEquals(expectedTable, actualTable);

  }

  @Test
  public void testUpdate() throws Exception{
    //Definimos el modelo que va a entrar al sql
    Cliente cliente =  new Cliente(1,"John", "Smith");
    cliente.setDireccion("Other Street");
    cliente.setCiudad("NewCity");

    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-esperado.xml");
    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    Assertions.assertDoesNotThrow(()->clienteDAO.update(cliente));

    IDataSet databaseDataSet = connection.createDataSet();
    ITable actualTable = databaseDataSet.getTable("cliente");

    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-esperado-apartadoD.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);
  }

  @Test
  public void clienteEsperado() throws Exception{
    Cliente clienteEsperado = new Cliente(1,"John", "Smith");
    clienteEsperado.setDireccion("1 Main Street");
    clienteEsperado.setCiudad("Anycity");

    //Inicializamos la bd
    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-esperado.xml");
    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    //Invocamos a nuestro sut
    int idaRecuperar = 1;

    Cliente clienteRecuperado = Assertions.assertDoesNotThrow(()->clienteDAO.retrieve(idaRecuperar));

    Assertions.assertAll(
            ()->Assertions.assertEquals(clienteEsperado.getId(), clienteRecuperado.getId()),
            ()->Assertions.assertEquals(clienteEsperado.getNombre(), clienteRecuperado.getNombre()),
            ()->Assertions.assertEquals(clienteEsperado.getApellido(), clienteRecuperado.getApellido()),
            ()->Assertions.assertEquals(clienteEsperado.getDireccion(), clienteRecuperado.getDireccion()),
            ()->Assertions.assertEquals(clienteEsperado.getCiudad(), clienteRecuperado.getCiudad())
    );

  }


  }