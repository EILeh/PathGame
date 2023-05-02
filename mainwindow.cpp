#include "gameboard.hh"
#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameBoard_()
{
    ui->setupUi(this);

    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonReset->setEnabled(false);

    timer = new QTimer(parent);
    gameBoard_ = new GameBoard;

    connect(timer, &QTimer::timeout, this, &MainWindow::updateLcd);

    connect(ui->pushButtonStart, &QPushButton::clicked, this,
            &MainWindow::startTimer);

    connect(ui->pushButtonReset, &QPushButton::clicked, this,
            &MainWindow::resetGame);

    connect(ui->pushButtonClose, &QPushButton::clicked, this,
            &MainWindow::closeGame);

    initButtons();

}


MainWindow::~MainWindow()
{
    delete ui;
}


// Pelissä käytetyt värikoodit tarkentamaan, mitä mikäkin koodi tarkoittaa.
// VÄRIT:
// harmaa: #e4e4e4
// punainen: #f28383
// punainen valittu: #9f4e4e
// vihreä: #93ed95
// vihreä valittu: #2b722d


// Muodostaa pelilaudan sekä määrittä ominaisuudet painikkeille.
void MainWindow::initButtons()
{
    // Asettaa napeille paikat ja koot käymällä läpi for-loopissa nappien
    // määrän.
    for ( int i = 0; i < 12; i++ )
    {
        // Luo uuden painikkeen button ja asettaa sille vakiokoon käyttämällä
        // QWidget-luokkaan kuuluvaa setFixedSize-metodia.
        QPushButton *button = new QPushButton(this);
        button->setFixedSize(SIDELENGTH, SIDELENGTH);
        button->setEnabled(false);

        // Asettaa neljälle painikkeelle ominaisuudet metodilla setProperty si-
        // ten, että ensimmäisenä parametrina on ominaisuuden nimi "color" ja
        // toisena parametrina ominaisuuden "color" arvo eli "green".
        if ( i < 4 )
        {
            button->setProperty("color", "green");

            // Asettaa metodilla setStyleSheet painikkeiden väriksi #93ed95.
            // vihreä: #93ed95
            button->setStyleSheet("background-color: #93ed95");

            // Asettaa painikkeille paikat käyttämällä move-metodia, jossa en-
            // simmäinen parametri BUTTONPOSITION on x-suuntainen sijainti
            // ja toinen parametri TOPROWY on y-suuntainen sijainti. Vakio
            // BUTTONPOSITION kerrotaan muuttujalla i, jotta painikkeet saadaan
            // asetettua vierekkäin tasaisin välein.
            button->move(BUTTONPOSITION * i, TOPROWY);
        }

        // Asettaa yksittäiselle painikkeelle ominaisuuden metodilla setProperty
        // siten, että ensimmäisenä parametrina on ominaisuuden nimi "color" ja
        // toisena parametrina ominaisuuden "color" arvo eli "gray".
        else if ( i == 4 )
        {
            button->setProperty("color", "gray");

            // Asettaa metodilla setStyleSheet painikkeen väriksi #e4e4e4.
            // harmaa: #e4e4e4
            button->setStyleSheet("background-color: #e4e4e4");

            // Asettaa painikkeille paikat käyttämällä move-metodia, jossa para-
            // metreina on BUTTONPOSITION kerrottuna kahdella, jotta painikkeen
            // sijainti saadaan oikealle kohdalle x- ja y-suunnassa.
            button->move(BUTTONPOSITION * 2, BUTTONPOSITION * 2);
        }

        // Asettaa neljälle painikkeelle ominaisuudet metodilla setProperty si-
        // ten, että ensimmäisenä parametrina on ominaisuuden nimi "color" ja
        // toisena parametrina ominaisuuden "color" arvo eli "gray".
        else if ( i < 8 )
        {
            button->setProperty("color", "gray");

            // Asettaa metodilla setStyleSheet painikkeiden väriksi #e4e4e4.
            // harmaa: #e4e4e4
            button->setStyleSheet("background-color: #e4e4e4");

            // Asettaa painikkeille paikat käyttämällä move-metodia, jossa en-
            // simmäinen parametri BUTTONPOSITION on x-suuntainen sijainti ja
            // toinen parametri on BUTTONPOSITION kerrottuna i:n arvo, josta on
            // vähennetty FIVEBUTTONWITHPOSITION. FIVEBUTTONWITHPOSITION kertoo
            // painikkeiden määrän, joille on jo asetettu sijainti pelilaudalla.
            // Saatuun lukuun lisätään vielä vakio BUTTONPOSITION, jotta painik-
            // keet saadaan asetettua vierekkäin tasaisin välein.
            button->move(BUTTONPOSITION, BUTTONPOSITION *
                         (i - FIVEBUTTONSWITHPOSITION) + BUTTONPOSITION);
        }

        // Asettaa neljälle painikkeelle ominaisuudet metodilla setProperty si-
        // ten, että ensimmäisenä parametrina on ominaisuuden nimi "color" ja
        // toisena parametrina ominaisuuden "color" arvo eli "red".
        else if ( i < 12 )
        {

            button->setProperty("color", "red");

            // Asettaa metodilla setStyleSheet painikkeiden väriksi #f28383.
            // punainen: #f28383
            button->setStyleSheet("background-color: #f28383");

            // Asettaa painikkeille paikat käyttämällä move-metodia, jossa en-
            // simmäinen parametri on BUTTONPOSITION kerrottuna i:n arvo, josta
            // on vähennetty EIGHTBUTTONWITHPOSITION. EIGHTBUTTONWITHPOSITION
            // kertoo painikkeiden määrän, joille on jo asetettu sijainti peli-
            // laudalla. Toinen parametri BUTTONPOSITION on x-suuntainen sijain-
            // ti kerrottuna neljällä, jotta painikkeet saadaan asetettua vie-
            // rekkäin tasaisin välein.
            button->move(BUTTONPOSITION * (i - EIGHTBUTTONSWITHPOSITION),
                         BUTTONPOSITION * 4);
        }


        // Yhdistää signaalit nappeihin käyttämällä lambda-funktiota, joka vä-
        // littää kaksi parametria. Parametri "this" viittaa nykyiseen olioon,
        // joka sisältää painikkeen "button". Käyttäjän klikatessa painiketta
        // aktivoituu lambda-funktio ja kutsuu funktiota selectButton.
        connect(button, &QPushButton::clicked, [this, button]()
        {
            selectButton(button);
        });

        // Lisää painikkeet vektoriin buttons_, jotta niiden alkuperäiset si-
        // jainnit saadaan talteen.
        buttons_.push_back(button);

        // Asettaa napit näkyviksi käyttöliittymässä.
        button->setVisible(true);
    }

    // Asetetaan selectedButton_ arvoksi nullptr, sillä yhtäkään nappia ei ole
    // valittu.
    selectedButton_ = nullptr;
}


// Tarkistaa onko selectedButton_ muuttujassa jo painike eli onko käyttäjä jo
// valinnut siirrettävän painikkeen. Jos painiketta ei ole valittu eli muuttujan
// selectedButton_ arvo on nullptr, asetetaan klikatun painikkeen arvo tähän
// muuttujaan. Jos selectedButton_ arvo ei ole nullptr, on kyseessä painike, jo-
// hon selectedButton_ sisältämä tieto halutaan siirtää. Siirron oikeellisuus
// tarkistetaan ja siirto tehdään, jos se on mahdollinen.
void MainWindow::selectButton(QPushButton *button)
{
    // Jos selectedButton_ arvo on nullptr, käyttäjä ei ole vielä klikannut pai-
    // niketta, jonka haluaa siirtää.
    if ( selectedButton_ == nullptr )
    {
        // Tallennetaan muuttujaan color tieto painikkeen button ominaisuuden
        // "color" arvo merkkijonona.
        QString color = button->property("color").toString();

        // Jos color arvo on "green", muutetaan painikkeen väriä.
        if ( color == "green" )
        {
            // vihreä valittu: #2b722d
            button->setStyleSheet("background-color: #2b722d");
        }

        // Jos color arvo on "red", muutetaan painikkeen väriä.
        else if ( color == "red" )
        {
            // punainen valittu: #9f4e4e
            button->setStyleSheet("background-color: #9f4e4e");
        }

        // Jos valittu painike on harmaa eli tyhjä, palataan takaisin kutsufunk-
        // tioon eikä pelissä tapahdu mitään.
        else
        {
            return;
        }

        // Tallennetaan selectedButton_ muuttujaan button, jolloin saadaan tal-
        // teen tieto, minkä painikkeen käyttäjä on valinnut.
        selectedButton_ = button;
    }

    // Jos käyttäjä on valinnut jo siirrettävän painikkeen, valitsee hän toisel-
    // la klikkauksella joko uuden paikan painikkeelle tai klikkaamalla samaa
    // painiketta uudestaa, poistaa käyttäjä kyseisen painikkeen valinnan.
    else
    {
        // Tallennetaan muuttujaan color1 tieto painikkeen selectedButton_ omi-
        // naisuuden "color" arvo merkkijonona.
        QString color1 = selectedButton_->property("color").toString();

        // Tallennetaan muuttujaan color2 tieto painikkeen button ominaisuuden
        // "color" arvo merkkijonona.
        QString color2 = button->property("color").toString();

        // Asettaa selectedButton_ ominaisuuden "color" arvoksi muuttujan color2
        // arvon, joka on toisena klikatun painikkeen ominaisuuden "color" arvo.
        selectedButton_->setProperty("color", color2);

        // Asettaa button ominaisuuden "color" arvoksi muuttujan color1 arvon,
        // joka on ensimmäisenä klikatun painikkeen ominaisuuden "color" arvo.
        button->setProperty("color", color1);

        // Jos color1 arvo on "green" ja color2 arvo on "gray" kutsutaan funk-
        // tiota greenToGray. Tarkistetaan, onko tehty siirto voittosiirto kut-
        // sumalla funktiota gameStatus.
        if ( color1 == "green" && color2 == "gray" )
        {
            greenToGray(color1, color2, button);

            if ( gameStatus() )
            {
                // Jos funktio gameStatus palauttaa totuusarvon true, kutsutaan
                // funktiota gameWon.
                gameWon();

            }
        }

        // Jos color1 arvo on "greeen" ja color2 arvo on "green" kutsutaan funk-
        // tiota greenToGray.
        else if ( color1 == "green" && color2 == "green" )
        {
            greenToGreen(color1, color2, button);
        }

        // Jos color1 arvo on "green" ja color2 arvo on "red" kutsutaan funk-
        // tiota greenToGray.
        else if ( color1 == "green" && color2 == "red" )
        {
            greenToRed(color1, color2, button);
        }

        // Jos color1 arvo on "red" ja color2 arvo on "gray" kutsutaan funk-
        // tiota greenToGray. Tarkistetaan, onko tehty siirto voittosiirto kut-
        // sumalla funktiota gameStatus.
        else if ( color1 == "red" && color2 == "gray" )
        {
            redToGray(color1, color2, button);

            if ( gameStatus() )
            {
                // Jos funktio gameStatus palauttaa totuusarvon true, kutsutaan
                // funktiota gameWon.
                gameWon();

            }
        }

        // Jos color1 arvo on "red" ja color2 arvo on "red" kutsutaan funk-
        // tiota greenToGray.
        else if ( color1 == "red" && color2 == "red" )
        {
            redToRed(color1, color2, button);
        }

        // Jos color1 arvo on "red" ja color2 arvo on "green" kutsutaan funk-
        // tiota greenToGray.
        else if ( color1 == "red" && color2 == "green" )
        {
            redToGreen(color1, color2, button);
        }

        // Asetetaan muuttujan selectedButton_ arvoksi nullptr, jotta käyttäjä
        // voi taas valita uuden siirrettävän painikkeen.
        selectedButton_ = nullptr;

    }
}


// Käyttäjän voittaessa pelin funktio antaa hänelle ilmoituksen, pysäyttää ajas-
// timen eikä käyttäjä pystyy enää tekemään siirtoja.
void MainWindow::gameWon()
{
    // Ilmoitetaan pelaajalle, että hän on voittanut.
    writtenText_ = "You Won!";
    ui->labelInfo->setText(writtenText_);

    // Pysäyttää ajastimen, jotta käyttäjä näkee aikansa.
    timer->stop();

    // Asetetaan pelin päättymisen jälkeen kaikki napit pois käy-
    // töstä, kunnes käyttäjä klikkaa joko Reset.
    setButtonsEnabled(false);
}

// Tarkistaa onko käyttäjän viimeisin siirto ollut voittosiirto ja palauttaa sen
// mukaan totuusarvon.
bool MainWindow::gameStatus()
{

    // Jos funktio is_game_over palauttaa totuusarvon true, on viimeisin siirto
    // ollut voittosiirto, jolloin myös funktio gameStatus palauttaa arvon true.
    if ( gameBoard_->is_game_over() )
    {
        return true;
    }

    // Jos funktio is_game_over palauttaa totuusarvon false, on viimeisin siirto
    // ollut voittosiirto, jolloin myös funktio gameStatus palauttaa arvon
    // false.
    return false;
}


// Tarkistaa, mikä on siirrettävän painikkeen alkusijainti ja palauttaa tiedon
// painikkeen sijainnista.
Point MainWindow::checkStartPosition()
{
    // Annetaan muuttujalle startRow tieto, joka sisältää valitun painikkeen
    // alkusijainnin rivillä.
    int startRow = selectedButton_->pos().y() / GETCORRECTROWPOSITION;

    // Koska rivejä on laudalla viisi, mutta laskeminen alkaa jo nollasta, täy-
    // tyy tehdä ehto, joka tarkistaa, että painikkeen rivin alkusijainti on
    // maksimissaan neljä.
    if ( startRow >= 5 )
    {
        startRow = 4;
    }

    // Annetaan muuttujalle startColumn tieto, joka sisältää valitun painikkeen
    // alkusijainnin sarakkeella.
    int startColumn = selectedButton_->pos().x() / GETCORRECTCOLUMNPOSITION;

    // Koska sarakkeita on laudalla neljä, mutta laskeminen alkaa jo nollasta,
    // täytyy tehdä ehto, joka tarkistaa, että painikkeen rivin alkusijainti on
    // maksimissaan kolme.
    if ( startColumn >= 4 )
    {
        startColumn = 3;
    }

    // Asetetaan muuttujaan start tieto painikkeen alkusijainnista ja palaute-
    // taan tieto.
    Point start = {startColumn, startRow};

    return start;
}


// Tarkistaa, mikä on painikkeen sijainti, johon selectedButton_ halutaan siir-
// tää ja palauttaa tiedon painikkeen sijainnista.
Point MainWindow::checkDestionation(QPushButton *button)
{
    // Annetaan muuttujalle destinationRow, joka sisältää painikkeen, johon va-
    // littu nappi halutaan siirtää, tieto sen alkusijainnista rivillä.
    int destinationRow = button->pos().y() / GETCORRECTROWPOSITION;

    // Koska rivejä on laudalla viisi, mutta laskeminen alkaa jo nollasta, täy-
    // tyy tehdä ehto, joka tarkistaa, että painikkeen rivin alkusijainti on
    // maksimissaan neljä.
    if ( destinationRow >= 5 )
    {
        destinationRow = 4;
    }

    // Annetaan muuttujalle destinationColumn, joka sisältää painikkeen, johon
    // valittu nappi halutaan siirtää, tieto sen alkusijainnista sarakkeella.
    int destinationColumn = button->pos().x() / GETCORRECTCOLUMNPOSITION;

    // Koska sarakkeita on laudalla neljä, mutta laskeminen alkaa jo nollasta,
    // täytyy tehdä ehto, joka tarkistaa, että painikkeen rivin alkusijainti on
    // maksimissaan kolme.
    if ( destinationColumn >= 4 )
    {
        destinationColumn = 3;
    }

    // Asetetaan muuttujaan destination tieto painikkeen sijainnista ja palaute-
    // taan tieto.
    Point destination = {destinationColumn, destinationRow};

    return destination;
}


// Asettaa selectedButton_ ominaisuuden "color" arvoksi muuttujan color1 arvon,
// joka oli aiemmin muutettu toisena klikatun painikkeen ominaisuuden "color"
// arvo. Asettaa myös button ominaisuuden "color" arvoksi muuttujan color2 ar-
// von, joka oli aiemmin muutettu ensimmäisenä klikatun painikkeen ominaisuuden
// "color" arvo.
void MainWindow::setPropertyToButton(QString color1, QString color2,
                                     QPushButton *button)
{
    selectedButton_->setProperty("color", color1);
    button->setProperty("color", color2);

}


// Asettaa writtenText_ arvoksi tyhjän merkkijonon siltä varalta, että aikaisem-
// pi siirto olisi aiheuttanut sen lisäämisen.
void MainWindow::resetText()
{
    // Poistetaan mahdollinen teksti.
    writtenText_ = "";
    ui->labelInfo->setText(writtenText_);
}


// Tarkistaa voiko käyttäjän valitsemaa painiketta siirtää paikalle, johon hän
// sen haluaa. Tekee toiminnon sen mukaan, mitä funktiosta move palautuu.
void MainWindow::greenToGray(QString color1, QString color2,
                             QPushButton *button)
{

    // Kutsutaan funktiota resetText, joka poistaa tekstin, jos sellainen on
    // lisätty.
    resetText();

    // Tallennetaan muuttujaan start tieto valitun painikkeen alkusijainnista.
    // Alkusijainti saadaan kutsumalla funktiota checkStartPosition.
    Point start = checkStartPosition();

    // Tallennetaan muuttujaan destination tieto siitä sijainnista, mihin valit-
    // tu painike halutaan siirtää.
    Point destination = checkDestionation(button);

    // Jos move funktio palauttaa arvon true, on tehtävä siirto sallittu ja voi-
    // daan se myös tehdä. Vaihdetaan painikkeiden värit keskenään sekä kutsu-
    // taan funktiota moveCounter.
    if ( gameBoard_->move(start, destination) )
    {
        // harmaa: #e4e4e4
        // vihreä: #93ed95
        selectedButton_->setStyleSheet("background-color: #e4e4e4;");
        button->setStyleSheet("background-color: #93ed95;");
        moveCounter();

    }

    // Jos move funktio palauttaa arvon false, ei tehtävä siirto tällöin ole
    // sallittu ja käyttäjälle annetaan tieto tästä.
    else
    {
        writtenText_ = "You are not allowed to make that move!";
        ui->labelInfo->setText(writtenText_);

        // Muuttujan selectedButton_ väri muutetaan takaisin väriksi #93ed95.
        selectedButton_->setStyleSheet("background-color: #93ed95;");

        // Kutsutaan funktiota setPropertyToButton.
        setPropertyToButton(color1, color2, button);
    }
}

// Tarkistaa haluaako käyttäjä poistaa valinnan painikkeesta vai yrittääkö hän
// siirtää vihreää painikettä toisen vihreän painikkeen paikalle.
void MainWindow::greenToGreen(QString color1, QString color2,
                              QPushButton *button)
{
    // Kutsutaan funktiota resetText, joka poistaa tekstin, jos sellainen on
    // lisätty.
    resetText();

    // Tallennetaan muuttujaan start tieto valitun painikkeen alkusijainnista.
    // Alkusijainti saadaan kutsumalla funktiota checkStartPosition.
    Point start = checkStartPosition();

    // Tallennetaan muuttujaan destination tieto siitä sijainnista, mihin valit-
    // tu painike halutaan siirtää.
    Point destination = checkDestionation(button);

    // Jos alkusijainti on sama kuin loppusijainti, on käyttäjä tällöin klikan-
    // nut samaa painiketta kaksi kertaa eli kyseisen painikkeen valinta pois-
    // tetaan.
    if ( start == destination )
    {
        // Muuttujan selectedButton_ väri muutetaan takaisin väriksi #93ed95.
        selectedButton_->setStyleSheet("background-color: #93ed95;");

        // Kutsutaan funktiota setPropertyToButton.
        setPropertyToButton(color1, color2, button);

        // Asetetaan muuttujan selectedButton_ arvoksi nullptr, jotta käyttäjä
        // voi taas valita uuden siirrettävän painikkeen.
        selectedButton_ = nullptr;

        // Palataan takaisin kutsufunktioon.
        return;
    }

    // Jos käyttäjä klikkaa kahta eri vihreää painiketta, asetaan valitun pai-
    // nikkeen väriksi #93ed95 ja annetaan ilmoitus, että paikka, johon pai-
    // nike halutaan siirtää, ei ole tyhjä.
    selectedButton_->setStyleSheet("background-color: #93ed95;");
    writtenText_ = "Choose an empty spot!";
    ui->labelInfo->setText(writtenText_);

    // Kutsutaan funktiota setPropertyToButton.
    setPropertyToButton(color1, color2, button);

}


// Kun käyttäjä yrittää siirtää vihreää painikettä punaisen painikkeen paikalle,
// funktio antaa ilmoituksen, että siirto ei ole mahdollinen.
void MainWindow::greenToRed(QString color1, QString color2, QPushButton *button)
{
    // Kutsutaan funktiota resetText, joka poistaa tekstin, jos sellainen on
    // lisätty.
    resetText();

    // Jos käyttäjä klikkaa kahta eri vihreää painiketta, asetaan valitun pai-
    // nikkeen väriksi #93ed95 ja annetaan ilmoitus, että paikka, johon pai-
    // nike halutaan siirtää, ei ole tyhjä.
    selectedButton_->setStyleSheet("background-color: #93ed95;");
    writtenText_ = "Choose an empty spot!";
    ui->labelInfo->setText(writtenText_);

    // Kutsutaan funktiota setPropertyToButton.
    setPropertyToButton(color1, color2, button);

}


// Tarkistaa voiko käyttäjän valitsemaa painiketta siirtää paikalle, johon hän
// sen haluaa. Tekee toiminnon sen mukaan, mitä funktiosta move palautuu.
void MainWindow::redToGray(QString color1, QString color2, QPushButton *button)
{
    // Kutsutaan funktiota resetText, joka poistaa tekstin, jos sellainen on
    // lisätty.
    resetText();

    // Tallennetaan muuttujaan start tieto valitun painikkeen alkusijainnista.
    // Alkusijainti saadaan kutsumalla funktiota checkStartPosition.
    Point start = checkStartPosition();

    // Tallennetaan muuttujaan destination tieto siitä sijainnista, mihin valit-
    // tu painike halutaan siirtää.
    Point destination = checkDestionation(button);

    // Jos move funktio palauttaa arvon true, on tehtävä siirto sallittu ja voi-
    // daan se myös tehdä. Vaihdetaan painikkeiden värit keskenään sekä kutsu-
    // taan funktiota moveCounter.
    if ( gameBoard_->move(start, destination) )
    {
        // harmaa: #e4e4e4
        // punainen: #f28383
        selectedButton_->setStyleSheet("background-color: #e4e4e4;");
        button->setStyleSheet("background-color: #f28383;");
        moveCounter();
    }

    // Jos move funktio palauttaa arvon false, ei tehtävä siirto tällöin ole
    // sallittu ja käyttäjälle annetaan tieto tästä.
    else
    {
        writtenText_ = "You are not allowed to make that move!";
        ui->labelInfo->setText(writtenText_);

        // Muuttujan selectedButton_ väri muutetaan takaisin väriksi #f28383
        selectedButton_->setStyleSheet("background-color: #f28383;");

        // Kutsutaan funktiota setPropertyToButton.
        setPropertyToButton(color1, color2, button);

    }
}


// Tarkistaa haluaako käyttäjä poistaa valinnan painikkeesta vai yrittääkö hän
// siirtää punaista painikettä toisen punaisen painikkeen paikalle.
void MainWindow::redToRed(QString color1, QString color2, QPushButton *button)
{
    // Kutsutaan funktiota resetText, joka poistaa tekstin, jos sellainen on
    // lisätty.
    resetText();

    // Tallennetaan muuttujaan start tieto valitun painikkeen alkusijainnista.
    // Alkusijainti saadaan kutsumalla funktiota checkStartPosition.
    Point start = checkStartPosition();

    // Tallennetaan muuttujaan destination tieto siitä sijainnista, mihin valit-
    // tu painike halutaan siirtää.
    Point destination = checkDestionation(button);

    // Jos alkusijainti on sama kuin loppusijainti, on käyttäjä tällöin klikan-
    // nut samaa painiketta kaksi kertaa eli kyseisen painikkeen valinta pois-
    // tetaan.
    if ( start == destination )
    {
        // Muuttujan selectedButton_ väri muutetaan takaisin väriksi #f28383
        selectedButton_->setStyleSheet("background-color: #f28383;");

        // Kutsutaan funktiota setPropertyToButton.
        setPropertyToButton(color1, color2, button);

        // Asetetaan muuttujan selectedButton_ arvoksi nullptr, jotta käyttäjä
        // voi taas valita uuden siirrettävän painikkeen.
        selectedButton_ = nullptr;

        // Palataan takaisin kutsufunktioon.
        return;
    }

    // Jos käyttäjä klikkaa kahta eri punaista painiketta, asetaan valitun pai-
    // nikkeen väriksi #f28383 ja annetaan ilmoitus, että paikka, johon pai-
    // nike halutaan siirtää, ei ole tyhjä.
    selectedButton_->setStyleSheet("background-color: #f28383;");
    writtenText_ = "Choose an empty spot!";
    ui->labelInfo->setText(writtenText_);

    // Kutsutaan funktiota setPropertyToButton.
    setPropertyToButton(color1, color2, button);

}


// Kun käyttäjä yrittää siirtää punaista painikettä vihreän painikkeen paikalle,
// funktio antaa ilmoituksen, että siirto ei ole mahdollinen.
void MainWindow::redToGreen(QString color1, QString color2, QPushButton *button)
{
    // Kutsutaan funktiota resetText, joka poistaa tekstin, jos sellainen on
    // lisätty.
    resetText();

    // Jos käyttäjä klikkaa kahta eri vihreää painiketta, asetaan valitun pai-
    // nikkeen väriksi #93ed95 ja annetaan ilmoitus, että paikka, johon pai-
    // nike halutaan siirtää, ei ole tyhjä.
    selectedButton_->setStyleSheet("background-color: #f28383;");
    writtenText_ = "Choose an empty spot!";
    ui->labelInfo->setText(writtenText_);

    // Kutsutaan funktiota setPropertyToButton.
    setPropertyToButton(color1, color2, button);

}


// Kun Start painiketta klikataan, poistetaan käyttäjältä mahdollisuus klikata
// Start painiketta uudestaa sekä otetaan Reset painike käyttöön. Kutsutaan
// funktiota setButtonsEnabled parametrilla true, jolloin käyttäjä saa myös
// kaikki pelin painikkeet käyttöönsä.
void MainWindow::startButtonClicked()
{
    ui->pushButtonStart->setEnabled(false);

    ui->pushButtonReset->setEnabled(true);

    setButtonsEnabled(true);

}


// Käyttäjän klikatessa painiketta Start, ajastin lähtee päälle sekä kutsutaan
// funktiota startButtonClicked.
void MainWindow::startTimer()
{
    timer->start(1000);
    time_ = 0;
    startButtonClicked();

}


// Käy läpi vektorin buttons_, joka sisältää tiedon kaikista painikkeista ja
// asettaa painikkeet joko käytettäviksi tai pois käytöstä sen perusteella, mi-
// kä on parametrin isButtonEnabled totuusarvo.
void MainWindow::setButtonsEnabled(bool isButtonEnabled)
{
    for (int i = 0; i < 12; i++ )
    {
        buttons_.at(i)->setEnabled(isButtonEnabled);
    }
}


// Tyhjentää vektorin buttons_, joka sisälsi tiedon aiemmin luoduista painik-
// keista, poistaa aiemmin luodun olion gameBoard_ sekä luo gameBoard_:sta uu-
// den olion. Uusi pelialusta luodaan kutsumalla funktiota initButtons sekä a-
// jastin aloitetaan alusta kutsumalla funktiota startTimer.
void MainWindow::resetGameBoard()
{
    buttons_.clear();
    delete gameBoard_;
    gameBoard_ = new GameBoard;
    initButtons();
    startTimer();
}


// Käyttäjän klikatessa painiketta Reset, alkaa koko peli alusta. Ajastin, siir-
// tolaskuri sekä pelilauta laitetaan alkutilaan.
void MainWindow::resetGame()
{
    // Tyhjennetään lcd:t, jotka sisältävät tiedot kuluneista sekunneista sekä
    // minuuteista ja tehdyistä siirroista.
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

    amountOfMoves_ = 0;
    ui->lcdNumberMoveCounter->display(0);

    // Kutsutaan funktiota resetText, joka poistaa tekstin, jos sellainen on
    // lisätty.
    resetText();

    // Asetetaan muuttujan selectedButton_ arvoksi nullptr, jotta mikään pai-
    // nike ei jää valituksi.
    selectedButton_ = nullptr;

    for ( int i = 0; i < 12; i++ )
    {
        delete buttons_.at(i);
    }

    resetGameBoard();

}


// Funktio päivittää ajastinta eli laskee sekunteja ja minuutteja.
void MainWindow::updateLcd()
{
    time_++;
    ui->lcdNumberMin->display(time_ / 60);
    ui->lcdNumberSec->display(time_ % 60);

}


// Käyttäjän klikatessa painiketta Close, suljetaan koko ohjelma.
void MainWindow::closeGame()
{
    this->close();

}


// Laskee käyttäjän tekemien siirtojen määrän kasvattamalla muuttujan
// amountOfMoves_ arvoa aina, kun moveCounter funktiota kutsutaan.
void MainWindow::moveCounter()
{
    amountOfMoves_++;
    ui->lcdNumberMoveCounter->display(amountOfMoves_);

}
