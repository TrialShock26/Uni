/*Compila i campi "Nome" e "Cognome" con le informazioni richieste
Nome: "Luca"
Cognome: "Sanselmo"
Username: l.sanselmo@studenti.unina.it
UserID: 1696
Date: 04/12/2025
*/

import org.junit.Before;
import org.junit.After;
import org.junit.BeforeClass;
import org.junit.AfterClass;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestHSLColor {
    HSLColor c1;
    HSLColor c2;

    @BeforeClass
	public static void setUpClass() {}

	@AfterClass
	public static void tearDownClass() {}

	@Before
	public void setUp() {
        c1 = new HSLColor();
        assertNotNull("Errore in costruzione", c1);

        c2 = new HSLColor();
        assertNotNull("Errore in costruzione", c2);
	}

	@After
	public void tearDown() {
        c1 = null;
        assertNull("Errore in distruzione", c1);
	}

	@Test
	public void testInitHSLbyRGB() {
        c1.initHSLbyRGB(255, 0, 0);
        assertEquals("Errore HSL by RGB: Hue", 0, c1.getHue());
        assertEquals("Errore HSL by RGB: Sat", 255, c1.getSaturation());
        // assertEquals("Errore HSL by RGB: Lum", 127, c1.getLuminence());
	}

	@Test
	public void testInitRGBbyHSL() {
        c2.initRGBbyHSL(0, 255, 127);
        // assertEquals("Errore RGB by HSL: Red", 255, c2.getRed());
        // assertEquals("Errore RGB by HSL: Green", 0, c2.getGreen());
        // assertEquals("Errore RGB by HSL: Blue", 0, c2.getBlue());
	}

	@Test
	public void testInitHSLbyRGBMax() {
        c1.initHSLbyRGB(255, 255, 255);
        // assertEquals("Errore HSL by RGB: Hue", 0, c1.getHue());
        assertEquals("Errore HSL by RGB: Sat", 0, c1.getSaturation());
        assertEquals("Errore HSL by RGB: Lum", 255, c1.getLuminence());
	}

	@Test
	public void testInitHSLbyRGBMin() {
        c1.initHSLbyRGB(0, 0, 0);
        // assertEquals("Errore HSL by RGB: Hue", 0, c1.getHue());
        assertEquals("Errore HSL by RGB: Sat", 0, c1.getSaturation());
        assertEquals("Errore HSL by RGB: Lum", 0, c1.getLuminence());
	}

	@Test
	public void testInitHSLbyRGBGreen() {
        c1.initHSLbyRGB(0, 255, 0);
        assertEquals("Errore HSL by RGB: Hue", 85, c1.getHue());
        assertEquals("Errore HSL by RGB: Sat", 255, c1.getSaturation());
        // assertEquals("Errore HSL by RGB: Lum", 127, c1.getLuminence());
	}

	@Test
	public void testInitHSLbyRGBBlue() {
        c1.initHSLbyRGB(0, 0, 255);
        assertEquals("Errore HSL by RGB: Hue", 170, c1.getHue());
        assertEquals("Errore HSL by RGB: Sat", 255, c1.getSaturation());
        // assertEquals("Errore HSL by RGB: Lum", 127, c1.getLuminence());
	}

	@Test
	public void testInitRGBbyHSLGreyScale() {
        c1.initRGBbyHSL(70, 0, 127);
        // assertEquals("Errore HSL by RGB: Red", 128, c1.getRed());
        // assertEquals("Errore HSL by RGB: Green", 128, c1.getGreen());
        // assertEquals("Errore HSL by RGB: Blue", 128, c1.getBlue());
	}

	@Test
	public void testHSLGetters() {
		c1.initHSLbyRGB(20, 20, 20);
		assertEquals("Errore getters: Red", 20, c1.getRed());
		assertEquals("Errore getters: Green", 20, c1.getGreen());
		assertEquals("Errore getters: Blue", 20, c1.getBlue());
	}

	@Test
	public void testHSLSetters() {
        c1.setHue(0);
        c1.setSaturation(0);
        c1.setLuminence(0);
        assertEquals("Errore setters: Hue", 0, c1.getHue());
        assertEquals("Errore setters: Sat", 0, c1.getSaturation());
        assertEquals("Errore setters: Lum", 0, c1.getLuminence());
        c1.setHue(-1);
        c1.setSaturation(-1);
        c1.setLuminence(-1);
        assertEquals("Errore setters: Hue", 254, c1.getHue());
        assertEquals("Errore setters: Sat", 0, c1.getSaturation());
        assertEquals("Errore setters: Lum", 0, c1.getLuminence());
        c1.setHue(1000);
        c1.setSaturation(1000);
        c1.setLuminence(1000);
        assertEquals("Errore setters: Hue", 235, c1.getHue());
        assertEquals("Errore setters: Sat", 255, c1.getSaturation());
        assertEquals("Errore setters: Lum", 255, c1.getLuminence());
	}

	@Test
	public void testHSLReverser() {
        c1.setHue(0);
		c1.reverseColor();
        assertEquals("Errore reverser: Hue", 127, c1.getHue());
	}

	@Test
	public void testHSLBrighten() {
		c1.brighten(0);
		c1.setLuminence(0);
		c1.brighten(10);
		c1.setLuminence(50);
		c1.brighten(50);
		c1.brighten(-1);
	}

	@Test
	public void testHSLBlend() {
		c2.blend(0, 0, 0, 2);
		c2.blend(0, 0, 0, 0);
		c2.blend(20, 30, 40, 0.6f);
	}
}