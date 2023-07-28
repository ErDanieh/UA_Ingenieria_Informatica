package ejercicio3.conPOyPFact;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.PageFactory;


import java.time.Duration;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestShoes {

    WebDriver driver;

    MyAccountPage poMyAccountPage;
    ShoesPage poShoesPage;

    ComparePage poComparePage;

    @BeforeAll
    public static void setupCookies(){
        Cookies.storeCookiesToFile("danielasensi444@outlook.com","ppssPassword123");
    }

    @BeforeEach
    public void setup(){
        driver = new ChromeDriver();
        driver.get("http://demo-store.seleniumacademy.com/customer/account/");
        Cookies.loadCookiesFromFile(driver);
        poMyAccountPage = PageFactory.initElements(driver, MyAccountPage.class);
    }


    @AfterEach
    public void teardown(){
        driver.close();
    }

    @Test
    public void compareShoes(){
        assertEquals("My Account", driver.getTitle());
        poShoesPage= poMyAccountPage.enterShoesPage();
        assertEquals("Shoes - Accessories", driver.getTitle());
        poShoesPage.clickShoesCompares(5);
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(5));
        poShoesPage.clickShoesCompares(6);
        poShoesPage.clickCompare();
        poComparePage = poShoesPage.cambiarVentanaCompare();
        assertEquals("Products Comparison List - Magento Commerce", driver.getTitle());
        poComparePage.cerrarVentanaCompare();
        assertEquals("Are you sure you would like to remove all products from your comparison?",poShoesPage.clearButtonClick());
    }


}
