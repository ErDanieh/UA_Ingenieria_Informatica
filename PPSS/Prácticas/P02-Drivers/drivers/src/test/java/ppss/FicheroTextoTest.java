package ppss;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class FicheroTextoTest {

    public FicheroTexto ficheroClass;

    @BeforeEach
    void setup(){
        this.ficheroClass = new FicheroTexto();
    }
    @Test
    void contarCaracteresC1(){
        String ruta = "src/main/resources/ficheroC1.txt";

        FicheroException exception = assertThrows(FicheroException.class, ()-> ficheroClass.contarCaracteres(ruta));
        assertEquals("src/main/resources/ficheroC1.txt (No existe el archivo o el directorio)", exception.getMessage());

    }

    @Test
    void contarCaracteresC2(){
        String ruta = "src/main/resources/ficheroCorrecto.txt";
        int resultado = assertDoesNotThrow(()-> ficheroClass.contarCaracteres(ruta));
        assertEquals(3, resultado);

    }

    @Tag("excluido")
    @Test
    void contarCaracteresC3(){
        //Assertions.fail();

    }

    @Tag("excluido")
    @Test
    void contarCaracteresC4(){
        //Assertions.fail();
    }
}