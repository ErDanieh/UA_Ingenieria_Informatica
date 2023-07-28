package ejercicio3.conPOyPFact;

import org.openqa.selenium.*;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.support.PageFactory;

import java.util.Set;

import java.time.Duration;

public class ShoesPage {

    WebDriver driver;
    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div[2]/div[2]/div[3]/ul/li[1]/div/div[2]/ul/li[2]/a")
    WebElement shoeCompare1;
    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div[2]/div[2]/div[3]/ul/li[2]/div/div[2]/ul/li[2]/a")
    WebElement shoeCompare2;

    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div[2]/div[2]/div[3]/ul/li[5]") WebElement shoeToCompareLi1;
    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div[2]/div[2]/div[3]/ul/li[6]") WebElement shoeToCompareLi2;
    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div[3]/div/div[2]/div/button") WebElement compareButton;

    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div[3]/div/div[2]/div/a") WebElement clearButton;


    public ShoesPage(WebDriver driver){
        this.driver = driver;
    }

    public void clickShoesCompares(int n){
        JavascriptExecutor jse = (JavascriptExecutor) driver;
        switch(n){
            case 5:
                jse.executeScript("arguments[0].scrollIntoView();", shoeToCompareLi1);
                shoeCompare1.click();
                break;
            case 6:
                jse.executeScript("arguments[0].scrollIntoView();", shoeToCompareLi2);
                shoeCompare2.click();
                break;
        }
    }

    public void clickCompare(){
        JavascriptExecutor jse  = (JavascriptExecutor) driver;
        jse.executeScript("arguments[0].scrollIntoView();", compareButton);

        compareButton.click();

    }

    public ComparePage cambiarVentanaCompare(){
        Set<String> setIds = driver.getWindowHandles();
        String[] handleIds = setIds.toArray(new String[setIds.size()]);
        driver.switchTo().window(handleIds[1]);
        return PageFactory.initElements(driver, ComparePage.class);
    }

    public String  clearButtonClick(){
        clearButton.click();
        //Operaciones sobre ventanas de alerta
        //cambiamos el foco a la ventana de alerta
        Alert alert = driver.switchTo().alert();
        //podemos obtener el mensaje de la ventana
        String mensaje = alert.getText();
        //podemos pulsar sobre el botón OK (si lo hubiese)
        alert.accept();
        return mensaje;
    }


}
