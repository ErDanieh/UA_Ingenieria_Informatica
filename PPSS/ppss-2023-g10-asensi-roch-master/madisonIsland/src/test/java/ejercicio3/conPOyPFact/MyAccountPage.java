package ejercicio3.conPOyPFact;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class MyAccountPage
{

    WebDriver driver;
    @FindBy(xpath = "//*[@id=\\\"nav\\\"]/ol/li[3]/a") WebElement accessoriesMenu;
    @FindBy(xpath = "//*[@id=\"nav\"]/ol/li[3]/ul/li[4]/a") WebElement shoesButton;

    public MyAccountPage(WebDriver driver){
        this.driver = driver;
        this.driver.get("http://demo-store.seleniumacademy.com/customer/account/");
    }

    public ShoesPage enterShoesPage(){
        //Muevo el ratón hasta Accesories para que se desplegue el menú (sin hacer click)
        Actions builder = new Actions(driver);
        builder.moveToElement(driver.findElement(By.xpath("//*[@id=\"nav\"]/ol/li[3]/a")));
        builder.perform();
        //Una vez desplegado el menú al hacer "hover" sobre accesories le doy click en shoes
        driver.findElement(By.xpath("//*[@id=\"nav\"]/ol/li[3]/ul/li[4]/a")).click();
        return PageFactory.initElements(driver, ShoesPage.class);
    }
}
