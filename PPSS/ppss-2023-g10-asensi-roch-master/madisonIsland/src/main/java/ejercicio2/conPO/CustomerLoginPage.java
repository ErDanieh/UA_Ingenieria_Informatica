package ejercicio2.conPO;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;

public class CustomerLoginPage {
    WebDriver driver;

    WebElement cuadroEmail;
    WebElement cuadroPassword;

    WebElement botonSubmit;

    WebElement mensajeError;
    public CustomerLoginPage(WebDriver driver){
        this.driver = driver;
        this.cuadroEmail = driver.findElement(By.id("email"));
        this.cuadroPassword = driver.findElement(By.id("pass"));
        this.botonSubmit = driver.findElement(By.id("send2"));
    }



    public void writeEmail(String email){
        cuadroEmail.clear();
        cuadroEmail.sendKeys(email);
    }

    public void writePassword(String password){
        cuadroPassword.sendKeys(password);
    }

    public void clickSubmit(){
        botonSubmit.click();
    }

    public WebElement getMensajeError(String email){
        cuadroEmail.sendKeys(email);
        cuadroPassword.sendKeys("sakljdfklsadfjklasdfjkl");
        botonSubmit.click();
        this.mensajeError = driver.findElement(By.xpath("//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div/div[2]/ul/li/ul/li/span"));
        return mensajeError;
    }
}

