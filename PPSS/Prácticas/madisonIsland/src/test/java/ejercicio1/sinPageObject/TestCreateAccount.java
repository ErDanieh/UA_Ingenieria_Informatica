package ejercicio1.sinPageObject;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;


import java.time.Duration;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;


public class TestCreateAccount {
    WebDriver driver;

    @BeforeEach
    public void setup(){
        driver = new ChromeDriver();
    }

    @AfterEach
    public void closeDriver(){
        //Cerramos la instancia del navegador
        driver.close();
    }

    @Tag("OnlyOnce")
    @Test
    public void createAccount(){
        driver.get("http://demo-store.seleniumacademy.com/");

        //Verifficamos que el titulo de la pagina es el correcto
        assertEquals("Madison Island", driver.getTitle());
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(5));
        //Seleccionamos account
        driver.findElement(By.xpath("//*[@id=\"header\"]/div/div[2]/div/a/span[2]")).click();
        //Seleccionamos el hiperenlace login
        driver.findElement(By.xpath("//*[@id=\"header-account\"]/div/ul/li[6]/a")).click();
        //Verificamos que el titulo de la pagina es Customer Login
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(5));
        assertEquals("Customer Login", driver.getTitle());
        //Seleccionamos el boton Create Account
        driver.findElement(By.xpath("//*[@id=\"login-form\"]/div/div[1]/div[2]/a/span/span")).click();
        //Verificamos el titulo Create new Customer Account
        assertEquals("Create New Customer Account", driver.getTitle());
        //Escribimos en los textboc
        driver.findElement(By.id("firstname")).sendKeys("Daniel");
        driver.findElement(By.id("middlename")).sendKeys("Asensi");
        driver.findElement(By.id("lastname")).sendKeys("Roch");
        driver.findElement(By.id("email_address")).sendKeys("danielasensi444@outlook.com");
        driver.findElement(By.id("password")).sendKeys("ppssPassword123");

        //Pulsamos el boton de register
        driver.findElement(By.xpath("//*[@id=\"form-validate\"]/div[2]/button")).click();

        //Comprobamos el mensaje de error por no haber marcado el check
        WebElement mensajeError = driver.findElement(By.id("advice-required-entry-confirmation"));
        assertEquals("This is a required field.", mensajeError.getText());
        //Escribo los datos que faltan
        driver.findElement(By.id("confirmation")).sendKeys("ppssPassword123");

        //Los vuelvo a enviar
        driver.findElement(By.xpath("//*[@id=\"form-validate\"]/div[2]/button")).click();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(5));
        assertEquals("My Account", driver.getTitle());

    }




}
