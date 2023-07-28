package ppss;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class MatriculaTest {
    int edad;
    boolean familiaNumerosa;
    boolean repetidor;
    float resultadoReal, resultadoEsperado;
    Matricula mat;

    @Test
    public void testCalculaTasaMatriculaC1() {
        edad = 23;
        familiaNumerosa = true;
        repetidor = true;
        resultadoEsperado = 250.00f;
        mat= new Matricula();
        resultadoReal = mat.calculaTasaMatricula(edad,familiaNumerosa,repetidor);
        //el tercer parámetro del método Assert.assertEquals es necesario si estamos comparando "floats"
        //en este caso el método devuelve cierto si:
        //resultadoEsperado = resultadoReal +/- 0.002
        assertEquals(resultadoEsperado, resultadoReal,0.002f);
    }

    @Test
    public void testCalculaMatriculaC2(){
        edad = 23;
        familiaNumerosa = false;
        repetidor = true;
        resultadoEsperado = 2000.00f;
        mat= new Matricula();
        resultadoReal = mat.calculaTasaMatricula(edad,familiaNumerosa,repetidor);
        //el tercer parámetro del método Assert.assertEquals es necesario si estamos comparando "floats"
        //en este caso el método devuelve cierto si:
        //resultadoEsperado = resultadoReal +/- 0.002
        assertEquals(resultadoEsperado, resultadoReal,0.002f);

    }

    @Test
    public void testCalculaMatriculaC3(){
        edad = 23;
        familiaNumerosa = false;
        repetidor = false;
        resultadoEsperado = 500.00f;
        mat= new Matricula();
        resultadoReal = mat.calculaTasaMatricula(edad,familiaNumerosa,repetidor);
        //el tercer parámetro del método Assert.assertEquals es necesario si estamos comparando "floats"
        //en este caso el método devuelve cierto si:
        //resultadoEsperado = resultadoReal +/- 0.002
        assertEquals(resultadoEsperado, resultadoReal,0.002f);

    }

    @Test
    public void testCalculaMatriculaC4(){
        edad = 53;
        familiaNumerosa = false;
        repetidor = false;
        resultadoEsperado = 400.00f;
        mat= new Matricula();
        resultadoReal = mat.calculaTasaMatricula(edad,familiaNumerosa,repetidor);
        //el tercer parámetro del método Assert.assertEquals es necesario si estamos comparando "floats"
        //en este caso el método devuelve cierto si:
        //resultadoEsperado = resultadoReal +/- 0.002
        assertEquals(resultadoEsperado, resultadoReal,0.002f);

    }

    @Test
    public void testCalculaMatriculaC5(){
        edad = 66;
        familiaNumerosa = false;
        repetidor = false;
        resultadoEsperado = 250.00f;
        mat= new Matricula();
        resultadoReal = mat.calculaTasaMatricula(edad,familiaNumerosa,repetidor);
        //el tercer parámetro del método Assert.assertEquals es necesario si estamos comparando "floats"
        //en este caso el método devuelve cierto si:
        //resultadoEsperado = resultadoReal +/- 0.002
        assertEquals(resultadoEsperado, resultadoReal,0.002f);

    }

    @Test
    public void testCalculaMatriculaC6(){
        edad =28;
        familiaNumerosa = true;
        repetidor = false;
        resultadoEsperado = 250.00f;
        mat= new Matricula();
        resultadoReal = mat.calculaTasaMatricula(edad,familiaNumerosa,repetidor);
        //el tercer parámetro del método Assert.assertEquals es necesario si estamos comparando "floats"
        //en este caso el método devuelve cierto si:
        //resultadoEsperado = resultadoReal +/- 0.002
        assertEquals(resultadoEsperado, resultadoReal,0.002f);

    }
}
