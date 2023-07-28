package ejercicio2.conPO;

import org.checkerframework.checker.units.qual.C;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;

import java.time.Duration;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestLogin2 {
    WebDriver driver;
    HomePage poHomePage;
    MyAccountPage poMyAccountPage;

    CustomerLoginPage poCustomerLoginPage;

    @BeforeEach
    public void setup(){
        driver = new ChromeDriver();
        driver.get("http://demo-store.seleniumacademy.com/");
        poHomePage = new HomePage(driver);


    }

    @AfterEach
    public void close(){
        driver.close();
    }
    @Test
    public void test_Login_Correct(){
        //Tiene que hacer lo mismo que loginOk
        assertEquals("Madison Island", driver.getTitle());
        poCustomerLoginPage = poHomePage.openLoginPage();
        assertEquals("Customer Login", driver.getTitle());
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(5));
        poCustomerLoginPage.writeEmail("danielasensi444@outlook.com");
        poCustomerLoginPage.writePassword("ppssPassword123");
        poCustomerLoginPage.clickSubmit();
        assertEquals("My Account", driver.getTitle());

    }
    @Test
    public void test_Login_Incorrect(){
        //Tiene que hacer lo mismo que loginFailed
        assertEquals("Madison Island", driver.getTitle());
        poCustomerLoginPage = poHomePage.openLoginPage();
        assertEquals("Customer Login", driver.getTitle());
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(5));
        WebElement mensajeError = poCustomerLoginPage.getMensajeError("danielasensi444@outlook.com");
        assertEquals("Invalid login or password.", mensajeError.getText());
    }

}
