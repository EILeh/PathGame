/* Polku
 *
 * VÄRIT:
 * harmaa: #e4e4e4
 * punainen: #f28383
 * punainen valittu: #9f4e4e
 * vihreä: #93ed95
 * vihreä valittu: #2b722d
 *
 *
 * Kuvaus:
 * Polku on peli, jossa käyttäjän on tarkoituksena siirrellä vihreitä ja punai-
 * sia pelinappuloita siten, että ne ovat päinvastaisessa järjestyksessä kuin
 * alussa.
 *
 *
 * Alku:
 * Pelin alussa vihreät painikkeet ovat pelialustan yläreunassa ja punaiset pai-
 * nikkeet ovat pelialustan alareunassa. Pelissä on ajastin, joka näyttää peliin
 * kuluneet minuutit ja sekunnit sekä laskuri, joka laskee tehdyt siirrot. Al-
 * kuun pelinappulat ovat pois käytöstä, kunnes käyttäjä klikkaa Start, jolloin
 * peli alkaa. Start-painiketta klikkaamalla ajastin käynnistuu ja pelinappuloi-
 * den siirtäminen on mahdollista.
 *
 *
 * Pelin toiminta:
 * Käyttäjä voi siirtää painiketta valitsemalla joko vihreän tai punaisen pai-
 * nikkeen klikkaamalla painiketta sekä harmaan kohdan, johon hän sen haluaa
 * siirtää klikkaamalla harmaata painiketta. Painikkeita ei voi siirtää toisten-
 * sa yli eli värillisen painikkeen voi siirtää vain harmaita painikkeita pit-
 * kin. Myöskään toisen värillisen painikkeen päälle voi laittaa painiketta ei-
 * kä harmaata painiketta ole mahdollistaa siirtää. Ohjelma myös ilmoittaa vir-
 * heellisistä siirroista.
 *
 *
 * Pelin päättyminen:
 * Peli päättyy, kun kaikki vihreät painikkeet ovat alareunassa ja kaikki pu-
 * naiset painikkeet ovat yläreunassa. Käyttäjä voi myös aloittaa pelin alusta
 * klikkaamalla Reset-painiketta joko kesken pelin tai pelin päätyttyä. Koko oh-
 * jelman sulkeminen onnistuu klikkaamalla Close-painiketta.
 *
 *
 * Ohjelman kirjoittaja
 *
 * Nimi: Elli Lehtimäki
 * Opiskelijanumero: 151309919
 * Käyttäjätunnus: nxelle
 * E-Mail: elli.i.lehtimaki@tuni.fi
 *
 */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:

    // Käyttäjän klikatessa painiketta Close, suljetaan koko ohjelma.
    void closeGame();

    // Laskee käyttäjän tekemien siirtojen määrän kasvattamalla muuttujan
    // amountOfMoves_ arvoa aina, kun moveCounter funktiota kutsutaan.
    void moveCounter();

    // Käyttäjän klikatessa painiketta Reset, alkaa koko peli alusta. Ajastin,
    // siirtolaskuri sekä pelilauta laitetaan alkutilaan.
    void resetGame();

    // Kun Start painiketta klikataan, poistetaan käyttäjältä mahdollisuus kli-
    // kata Start painiketta uudestaa sekä otetaan Reset painike käyttöön. Kut-
    // sutaan funktiota setButtonsEnabled parametrilla true, jolloin käyttäjä
    // saa myös kaikki pelin painikkeet käyttöönsä.
    void startButtonClicked();

    // Käyttäjän klikatessa painiketta Start, ajastin lähtee päälle sekä kutsu-
    // taan funktiota startButtonClicked.
    void startTimer();

    // Funktio päivittää ajastinta eli laskee sekunteja ja minuutteja.
    void updateLcd();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer* timer;

private:
    Ui::MainWindow *ui;

    // Tarkistaa onko käyttäjän viimeisin siirto ollut voittosiirto ja palauttaa
    // sen mukaan totuusarvon.
    bool gameStatus();

    // Alustetaan osoitin, joka osoittaa olioon, jonka tyyppi on GameBoard.
    GameBoard *gameBoard_;

    // Painikkeen sijainti, jonka avulla voidaan asettaa kaikki painikkeet ta-
    // saisesti pelilaudalle.
    const int BUTTONPOSITION = 70;

    // Vakio, jolla jakamalla saadaan sarakkeiden oikea sijainti.
    const int GETCORRECTCOLUMNPOSITION = 50;

    // Vakio, jolla jakamalla saadaan rivien oikea sijainti.
    const int GETCORRECTROWPOSITION = 60;

    // Vakio, joka kertoo, että kahdeksalla painikkeella on jo sijainti.
    const int EIGHTBUTTONSWITHPOSITION = 8;

    // Vakio, joka kertoo, että viidellä painikkeella on jo sijainti.
    const int FIVEBUTTONWITHPOSITION = 5;

    // Vakio yhden painikkeen yhden sivu pituudesta.
    const int SIDELENGTH = 60;

    // Vakio, joka kertoo ylimmän rivin y-suuntaisen sijainnin.
    const int TOPROWY = 0;

    // Muuttuja, jonka avulla saadaan selville tehtyjen siirtojen määrän.
    int amountOfMoves_ = 0;

    // Muuttuja, jonka avulla saadaan selville kulunut aika.
    int time_ = 0;

    // Tarkistaa, mikä on siirrettävän painikkeen alkusijainti ja palauttaa tie-
    // don painikkeen sijainnista.
    Point checkDestionation(QPushButton *button);

    // Tarkistaa, mikä on painikkeen sijainti, johon selectedButton_ halutaan
    // siirtää ja palauttaa tiedon painikkeen sijainnista.
    Point checkStartPosition();

    // Osoitin, joka osoittaa siihen painikkeeseen, jonka käyttäjä on valinnut.
    QPushButton *selectedButton_;

    // Muuttuja, joka sisältää tiedon tekstistä, joka halutaan käyttäjälle nä-
    // kyvän.
    QString writtenText_ = "";

    // Vektori, joka sisältää tiedon kaikista painikkeista.
    std::vector<QPushButton*> buttons_;

    // Muodostaa pelilaudan sekä määrittä ominaisuudet painikkeille.
    void initButtons();

    // Tarkistaa voiko käyttäjän valitsemaa painiketta siirtää paikalle, johon
    // hän sen haluaa. Tekee toiminnon sen mukaan, mitä funktiosta move
    // palautuu.
    void greenToGray(QString color1, QString color2, QPushButton *button);

    // Tarkistaa haluaako käyttäjä poistaa valinnan painikkeesta vai yrittääkö
    // hän siirtää vihreää painikettä toisen vihreän painikkeen paikalle.
    void greenToGreen(QString color1, QString color2, QPushButton *button);

    // Kun käyttäjä yrittää siirtää vihreää painikettä punaisen painikkeen pai-
    // kalle, funktio antaa ilmoituksen, että siirto ei ole mahdollinen.
    void greenToRed(QString color1, QString color2, QPushButton *button);

    // Tarkistaa voiko käyttäjän valitsemaa painiketta siirtää paikalle, johon
    // hän sen haluaa. Tekee toiminnon sen mukaan, mitä funktiosta move
    // palautuu.
    void redToGray(QString color1, QString color2, QPushButton *button);

    // Kun käyttäjä yrittää siirtää punaista painikettä vihreän painikkeen pai-
    // kalle, funktio antaa ilmoituksen, että siirto ei ole mahdollinen.
    void redToGreen(QString color1, QString color2, QPushButton *button);

    // Tarkistaa haluaako käyttäjä poistaa valinnan painikkeesta vai yrittääkö
    // hän siirtää punaista painikettä toisen punaisen painikkeen paikalle.
    void redToRed(QString color1, QString color2, QPushButton *button);

    // Tyhjentää vektorin buttons_, joka sisälsi tiedon aiemmin luoduista pai-
    // nikkeista, poistaa aiemmin luodun olion gameBoard_ sekä luo
    // gameBoard_:sta uuden olion. Uusi pelialusta luodaan kutsumalla funktiota
    // initButtons sekä ajastin aloitetaan alusta kutsumalla funktiota
    // startTimer.
    void resetGameBoard();

    // Tarkistaa onko selectedButton_ muuttujassa jo painike eli onko käyttäjä
    // jo valinnut siirrettävän painikkeen. Jos painiketta ei ole valittu eli
    // muuttujan selectedButton_ arvo on nullptr, asetetaan klikatun painikkeen
    // arvo tähän muuttujaan. Jos selectedButton_ arvo ei ole nullptr, on ky-
    // seessä painike, johon selectedButton_ sisältämä tieto halutaan siirtää.
    // Siirron oikeellisuus tarkistetaan ja siirto tehdään, jos se on
    // mahdollinen.
    void selectButton(QPushButton *button);

    // Käy läpi vektorin buttons_, joka sisältää tiedon kaikista painikkeista ja
    // asettaa painikkeet joko käytettäviksi tai pois käytöstä sen perusteella,
    // mikä on parametrin isButtonEnabled totuusarvo.
    void setButtonsEnabled(bool isButtonEnabled);

};
#endif // MAINWINDOW_HH
