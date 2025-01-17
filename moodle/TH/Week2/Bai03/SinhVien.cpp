#include "SinhVien.h"
#include <string.h>

// constructors
SinhVien::SinhVien()
{
    _fullname = NULL;
    _id = NULL;
    _birthday = NULL;
    _avg_mark = 0;

    _marks = NULL;
}

SinhVien::SinhVien(char *fullname, char *id, char *birthday, float *marks)
{
    _fullname = new char[strlen(fullname) + 1];
    if (fullname != NULL)
    {
        strcpy(_fullname, fullname);
    }

    _id = new char[strlen(id) + 1];
    if (_id != NULL)
    {
        strcpy(_id, id);
    }

    _birthday = new char[strlen(birthday) + 1];
    if (_birthday != NULL)
    {
        strcpy(_birthday, birthday);
    }

    _marks = new float[3];
    for (int i = 0; i < 3; i++)
    {
        _marks[i] = marks[i];
    }
}

// destructor
SinhVien::~SinhVien()
{
    // cout << "Destructor of SinhVien called.\n";
    delete _fullname;
    delete _id;
    delete _birthday;
    delete[] _marks;
}

// copy constructor
SinhVien::SinhVien(const SinhVien &src)
{
    _fullname = new char[strlen(src._fullname) + 1];
    strcpy(_fullname, src._fullname);

    _id = new char[strlen(src._id) + 1];
    strcpy(_id, src._id);

    _birthday = new char[strlen(src._birthday) + 1];
    strcpy(_birthday, src._birthday);

    _marks = new float[3];
    for (int i = 0; i < 3; i++)
    {
        _marks[i] = src._marks[i];
    }

    _avg_mark = src._avg_mark;
}

// assignment operator
SinhVien &SinhVien::operator=(const SinhVien &src)
{
    if (this != &src)
    {
        delete _fullname, _id, _birthday, _marks;

        _fullname = new char[strlen(src._fullname) + 1];
        strcpy(_fullname, src._fullname);

        _id = new char[strlen(src._id) + 1];
        strcpy(_id, src._id);

        _birthday = new char[strlen(src._birthday) + 1];
        strcpy(_birthday, src._birthday);

        _marks = new float[3];
        for (int i = 0; i < 3; i++)
        {
            _marks[i] = src._marks[i];
        }

        _avg_mark = src._avg_mark;
    }
    return *this;
}

// setters
void SinhVien::setName(char *name)
{
    if (_fullname != NULL)
    {
        delete _fullname;
    }
    _fullname = new char[strlen(name) + 1];
    strcpy(_fullname, name);
}

void SinhVien::setId(char *id)
{
    if (_id != NULL)
    {
        delete _id;
    }

    _id = new char[strlen(id) + 1];
    strcpy(_id, id);
}

void SinhVien::setBirthday(char *birthday)
{
    if (_birthday != NULL)
    {
        delete _birthday;
    }

    _birthday = new char[strlen(birthday) + 1];
    strcpy(_birthday, birthday);
}

void SinhVien::setMarks(float *marks)
{
    for (int i = 0; i < 3; i++)
    {
        _marks[i] = marks[i];
    }
}

void SinhVien::setMark_BT(float score)
{
    _marks[0] = score;
}

void SinhVien::setMark_GK(float score)
{
    _marks[1] = score;
}

void SinhVien::setMark_CK(float score)
{
    _marks[2] = score;
}

void SinhVien::calcAvg()
{
    _avg_mark = _marks[0] * 0.25 + _marks[1] * 0.25 + _marks[2] * 0.5;
}

// getters
char *SinhVien::fullname()
{
    return _fullname;
}

char *SinhVien::id()
{
    return _id;
}

char *SinhVien::birthday()
{
    return _birthday;
}

float *SinhVien::marks()
{
    return _marks;
}

float SinhVien::mark_BT()
{
    return _marks[0];
}

float SinhVien::mark_GK()
{
    return _marks[1];
}

float SinhVien::mark_CK()
{
    return _marks[2];
}

float SinhVien::avg_mark()
{
    calcAvg();
    return _avg_mark;
}

// friend functions

// standardize string
void standardize(char *&s)
{
    if (s == NULL)
    {
        return;
    }
    int i = 0;
    while (s[i] == ' ')
    {
        i++;
    }
    strncpy(s, s + i, strlen(s) - i + 1);
    i = strlen(s) - 1;
    while (s[i] == ' ')
    {
        i--;
    }
    s[i + 1] = '\0';
}

istream &operator>>(istream &in, SinhVien &src)
{
    cout << "Enter the information of a student following this format: \nID - Fullname - Birthday(dd/mm/yy) - BT GK CK\n";

    // declare a buffer to store the input
    char *pos = new char[100];

    // start to split the input
    // ID
    in.getline(pos, 100, '-');
    src.setId(pos);

    // Fullname
    in.getline(pos, 100, '-');
    src.setName(pos);

    // Birthday
    in.getline(pos, 100, '-');
    src.setBirthday(pos);
    // cout << "\nsplited ID: " << src._id << endl;
    // cout << "\nFullname: " << src._fullname << endl;
    // cout << "\nBirthday: " << src._birthday << endl;

    // standardize the strings
    standardize(src._id);
    standardize(src._fullname);
    standardize(src._birthday);
    // cout << "\nstandardized ID: " << src._id << endl;
    // cout << "\nFullname: " << src._fullname << endl;
    // cout << "\nBirthday: " << src._birthday << endl;

    // check if the next character is a space
    while (in.peek() == ' ')
    {
        in.ignore();
        // cout << "\nignore a space" << endl;
    }

    // Marks
    src._marks = new float[3];
    // cout << "\nBefore reading marks\n";

    // split marks from string input
    float score;

    // BT score
    in.getline(pos, 100, ' ');
    score = atof(pos);
    src._marks[0] = score;
    // cout << "\nBT score: " << score << endl;

    // GK score
    in.getline(pos, 100, ' ');
    score = atof(pos);
    src._marks[1] = score;
    // cout << "\nGK score: " << score << endl;

    // CK score
    in.getline(pos, 100, '\n');
    score = atof(pos);
    src._marks[2] = score;
    // cout << "\nCK score: " << score << endl;

    // cout << "\nAfter reading marks: ";
    // cout << src._marks[0] << " " << src._marks[1] << " " << src._marks[2] << endl;

    delete pos;
    // cout << "\nGet inform from input: done!\n";
    return in;
}

ostream &operator<<(ostream &os, SinhVien src)
{
    // ID - Fullname - Birthday - BT GK CK - AVG
    os << src._id << " - " << src._fullname << " - " << src._birthday << " - " << src._marks[0] << " " << src._marks[1] << " " << src._marks[2] << " - " << src.avg_mark() << endl;

    return os;
}

ifstream &operator>>(ifstream &fin, SinhVien &src)
{
    // read a line from the file
    char *line = new char[200];
    fin.getline(line, 200, '\n');

    // insert line into a stringstream
    stringstream in(line);

    // declare a buffer to store the input
    char *pos = new char[100];

    // start to split the input
    // ID
    in.getline(pos, 100, '-');
    src.setId(pos);
    standardize(src._id);

    // Fullname
    in.getline(pos, 100, '-');
    src.setName(pos);
    standardize(src._fullname);

    // Birthday
    in.getline(pos, 100, '-');
    src.setBirthday(pos);
    standardize(src._birthday);

    // check if the next character is a space
    while (in.peek() == ' ')
    {
        in.ignore();
    }

    // Marks : BT GK CK AVG
    src._marks = new float[3];
    float score;

    // BT
    in.getline(pos, 100, ' ');
    score = atof(pos);
    src._marks[0] = score;

    // GK
    in.getline(pos, 100, ' ');
    score = atof(pos);
    src._marks[1] = score;

    // CK
    in.getline(pos, 100, ' ');
    score = atof(pos);
    src._marks[2] = score;

    // AVG
    in.getline(pos, 100, ' ');
    score = atof(pos);
    src._avg_mark = score;

    delete pos;
    delete line;

    return fin;
}

ofstream &operator<<(ofstream &fout, SinhVien src)
{
    // ID - Fullname - Birthday - BT GK CK - AVG
    fout << src._id << " - " << src._fullname << " - " << src._birthday << " - " << src._marks[0] << " " << src._marks[1] << " " << src._marks[2] << " " << src.avg_mark() << endl;
    return fout;
}
