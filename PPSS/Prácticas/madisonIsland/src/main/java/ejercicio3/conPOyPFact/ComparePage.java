package ejercicio3.conPOyPFact;

import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;

import java.util.Set;

public class ComparePage {

    WebDriver driver;
    @FindBy(xpath = "//*[@id=\"top\"]/body/div/div[3]/button")
    WebElement cerrarVentanaCompare;

    public ComparePage(WebDriver driver){
        this.driver = driver;
    }

    public void cerrarVentanaCompare(){
        JavascriptExecutor jse = (JavascriptExecutor) driver;
        jse.executeScript("arguments[0].scrollIntoView();", cerrarVentanaCompare);

        cerrarVentanaCompare.click();

        Set<String> setIds = driver.getWindowHandles();
        String[] handleIds = setIds.toArray(new String[setIds.size()]);
        driver.switchTo().window(handleIds[0]);
    }


}
