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

public class TestSubjectParser {
	private SubjectParser sp1;
    private SubjectParser sp2;
    private SubjectParser sp3;
    private SubjectParser sp4;
    private SubjectParser sp5;
    private SubjectParser sp6;

	@BeforeClass
	public static void setUpClass() {
		// Eseguito una volta prima dell'inizio dei test nella classe
		// Inizializza risorse condivise 
		// o esegui altre operazioni di setup
	}

	@AfterClass
	public static void tearDownClass() {
		// Eseguito una volta alla fine di tutti i test nella classe
		// Effettua la pulizia delle risorse condivise 
		// o esegui altre operazioni di teardown
	}

	@Before
	public void setUp() {
		sp1 = new SubjectParser("1 Titolo (5/6)");
		assertNotNull("Errore in costruzione", sp1);

        sp2 = new SubjectParser("1 Titolo [5/6]");
		assertNotNull("Errore in costruzione", sp2);

        sp3 = new SubjectParser("SoggettoErrato");
		assertNotNull("Errore in costruzione", sp3);

        sp4 = new SubjectParser("0 SoggettoErrato 2a/b");
		assertNotNull("Errore in costruzione", sp4);

        sp5 = new SubjectParser("0 SoggettoErrato (2a/3b)");
		assertNotNull("Errore in costruzione", sp5);

        sp6 = new SubjectParser("0 SoggettoErrato (23)");
		assertNotNull("Errore in costruzione", sp6);
	}

	@After
	public void tearDown() {
		sp1 = null;
		assertNull("Errore in distruzione", sp1);
	}

	@Test
	public void testIdTondeNoSpazi() {
        long id = sp1.getId();
        assertEquals("Errore id", 1L, id);
	}

	@Test
	public void testTitoloTondeNoSpazi() {
        String tit = sp1.getTitle();
        assertEquals("Errore titolo", "Titolo ", tit);
	}

	@Test
	public void testRangeTondeNoSpazi() {
        String rg = sp1.getRangeString();
        assertEquals("Errore stringa range", "(5/6)", rg);
	}

	@Test
	public void testUpperRangeTondeNoSpazi() {
        int rg = sp1.getUpperRange();
        assertEquals("Errore upper range", 6, rg);
	}

	@Test
	public void testThisRangeTondeNoSpazi() {
        int rg = sp1.getThisRange();
        assertEquals("Errore this range", 5, rg);
	}

	@Test
	public void testIdQuadreNoSpazi() {
        long id = sp1.getId();
        assertEquals("Errore id", 1L, id);
	}

	@Test
	public void testTitoloQuadreNoSpazi() {
        String tit = sp2.getTitle();
        assertEquals("Errore titolo", "Titolo ", tit);
	}

	@Test
	public void testRangeQuadreNoSpazi() {
        String rg = sp2.getRangeString();
        assertEquals("Errore stringa range", "[5/6]", rg);
	}

	@Test
	public void testUpperRangeQuadreNoSpazi() {
        int rg = sp2.getUpperRange();
        assertEquals("Errore upper range", 6, rg);
	}

	@Test
	public void testThisRangeQuadreNoSpazi() {
        int rg = sp2.getThisRange();
        assertEquals("Errore this range", 5, rg);
	}

	@Test
	public void testWrongSubjectWithId() {
        long err = sp3.getId();
        assertEquals("Errore nel soggetto", -1, err);
	}

	@Test
	public void testWrongRangeWithThisRange() {
        int err = sp4.getThisRange();
        assertEquals("Errore nel soggetto", 1, err);
	}

	@Test
	public void testWrongRangeWithUpperRange() {
        int err = sp4.getUpperRange();
        assertEquals("Errore nel soggetto", 1, err);
	}

	@Test
	public void testWrongRangeWithBrackets() {
        int err = sp5.getThisRange();
        assertEquals("Errore nel soggetto", 1, err);
	}

	@Test
	public void testWrongRangeWithoutSlash() {
        int err = sp6.getThisRange();
        assertEquals("Errore nel soggetto", 1, err);
	}
}