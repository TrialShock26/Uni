/*Compila i campi "Nome" e "Cognome" con le informazioni richieste
Nome: "Luca"
Cognome: "Sanselmo"
Username: l.sanselmo@studenti.unina.it
UserID: 1696
Date: 09/12/2025
*/

import org.junit.Before;
import org.junit.After;
import org.junit.BeforeClass;
import org.junit.AfterClass;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestTennisScoreManager {
	TennisScoreManager t1;
	TennisScoreManager t2;
	TennisScoreManager t3;
	TennisScoreManager t4;
	TennisScoreManager t5;

	@BeforeClass
	public static void setUpClass() {}

	@AfterClass
	public static void tearDownClass() {}

	@Before
	public void setUp() {
		t1 = new TennisScoreManager();
		assertNotNull("Errore in costruzione", t1);
        
		t2 = new TennisScoreManager();
		assertNotNull("Errore in costruzione", t2);
        
		t3 = new TennisScoreManager();
		assertNotNull("Errore in costruzione", t3);
        
		t4 = new TennisScoreManager();
		assertNotNull("Errore in costruzione", t4);
        
		t5 = new TennisScoreManager();
		assertNotNull("Errore in costruzione", t5);
	}

	@After
	public void tearDown() {
		t1 = null;
		assertNull("Errore in distruzione", t1);
        
		t2 = null;
		assertNull("Errore in distruzione", t2);
        
		t3 = null;
		assertNull("Errore in distruzione", t3);
        
		t4 = null;
		assertNull("Errore in distruzione", t4);
        
		t5 = null;
		assertNull("Errore in distruzione", t5);
	}

	@Test
	public void testResetGameAndPoints() {
		t1.resetGameAndPoints();
	}

	@Test
	public void testIsGameOverFalse() {
		boolean test = t1.isGameOver();
		assertEquals("Errore Game Over", false, test);
	}

	@Test
	public void testPrintScoreStart() {
		t1.printScore();
	}

	@Test
	public void testPointScoredError() {
		t1.pointScored(100);
	}

	@Test
	public void testStompMatchP1() {
		for (int i = 0; i < 3; i++) {
            System.out.println(t2.getMatchScore());
			for (int j = 0; j < 6; j++) {
				for (int k = 0; k < 4; k++) {
					t2.pointScored(1);
				}
			}
		}
        t2.pointScored(1);
	}

	@Test
	public void testStompMatchP2() {
		for (int i = 0; i < 3; i++) {
            System.out.println(t3.getMatchScore());
			for (int j = 0; j < 6; j++) {
				for (int k = 0; k < 4; k++) {
					t3.pointScored(2);
				}
			}
		}
        t3.pointScored(2);
	}

	@Test
	public void testTieBreakAndDeuceP1() {
        boolean alt = true;
        boolean bigAlt = true;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 12; j++) {
                System.out.println(t4.getMatchScore());
                if (bigAlt) {
                    for (int k = 0; k < 7; k++) {
                        if (alt && k < 6) {
                            t4.pointScored(1);
                            alt = false;
                        } else if (k < 6) {
                            t4.pointScored(2);
                            alt = true;
                        } else {
                            t4.pointScored(1);
                            t4.pointScored(1);
                        }
                    }
                    bigAlt = false;
                } else {
                    for (int k = 0; k < 7; k++) {
                        if (alt && k < 6) {
                            t4.pointScored(1);
                            alt = false;
                        } else if (k < 6) {
                            t4.pointScored(2);
                            alt = true;
                        } else {
                            t4.pointScored(2);
                            t4.pointScored(2);
                        }
                    }
                    bigAlt = true;
                }
                if (j == 11) {
                    for (int k = 0; k < 7; k++) {
                        t4.pointScored(1);
                    }
                }
			}
		}
	}

	@Test
	public void testTieBreakAndDeuceP2() {
        boolean alt = true;
        boolean bigAlt = true;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 12; j++) {
                if (bigAlt) {
                    for (int k = 0; k < 7; k++) {
                        if (alt && k < 6) {
                            t5.pointScored(1);
                            alt = false;
                        } else if (k < 6) {
                            t5.pointScored(2);
                            alt = true;
                        } else {
                            t5.pointScored(1);
                            t5.pointScored(1);
                        }
                    }
                    bigAlt = false;
                } else {
                    for (int k = 0; k < 7; k++) {
                        if (alt && k < 6) {
                            t5.pointScored(1);
                            alt = false;
                        } else if (k < 6) {
                            t5.pointScored(2);
                            alt = true;
                        } else {
                            t5.pointScored(2);
                            t5.pointScored(2);
                        }
                    }
                    bigAlt = true;
                }
                if (j == 11) {
                    for (int k = 0; k < 7; k++) {
                        System.out.println(t5.getMatchScore());
                        t5.pointScored(2);
                    }
                }
			}
		}
	}
}