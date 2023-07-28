package ejercicio2.conPO;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;

public class HomePage {
    WebDriver driver;
    WebElement account;
    WebElement LoginButton;

    public HomePage(WebDriver driver){
        this.driver = driver;
        //Realizamos la conexion a la pagina principal

        //Sacamos el Account
        account = driver.findElement(By.xpath("//*[@id=\"header\"]/div/div[2]/div/a/span[2]"));
    }

    public WebElement getAccount(){
        return account;
    }

    public WebElement getLoginButton(){
        driver.findElement(By.xpath("//*[@id=\"header\"]/div/div[2]/div/a/span[2]")).click();
        this.LoginButton = driver.findElement(By.xpath("//*[@id=\"header-account\"]/div/ul/li[6]/a"));
        return  LoginButton;
    }

    public CustomerLoginPage openLoginPage(){
        getLoginButton().click();
        return new CustomerLoginPage(driver);
    }
}
