#pragma once
using namespace std;
sf::Color rcolor(bool isya);
int rsd(int from, int to);
int readrecord();
int writerecord(int towr);


int rsd(int from, int to)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(from, to);

    return (dist(gen));
}



sf::Color rcolor(bool isya) {

    int from, to;
    isya = false;
    if (isya == true) {
        from = 30;
        to = 100;
    }

    else {
        from = 150;
        to = 220;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(from, to);

    return (sf::Color(dist(gen), dist(gen), dist(gen)));
}

int readrecord() 
{
    int record;
    FILE* in = fopen("record.rcd","rb");
   
    if (in != NULL)
    {
        fread(&record,sizeof(int),1,in);
        fclose(in);
        return record;
    }
    return -1;
}


int writerecord(int towr)
{

    printf("a");
    FILE* ou = fopen("record.rcd", "wb");
    if (ou != NULL)
    {
        fwrite(&towr,sizeof(int),1,ou);
        fclose(ou);
        return 0;
    }

    return 1;
}
