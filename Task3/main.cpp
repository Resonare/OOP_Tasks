#include <iostream>
#include <fstream>
#include <chrono>
#include <map>

struct Note {
    std::string name;
    std::string phone;
    std::chrono::year_month_day birthday{};
};

void print (const Note& note) {
    std::cout << note.name << std::endl;
    std::cout << note.phone << std::endl;
    std::cout << static_cast<unsigned>(note.birthday.day()) << " ";
    std::cout << static_cast<unsigned>(note.birthday.month()) << " ";
    std::cout << static_cast<int>(note.birthday.year()) << std::endl;
}

bool readInput (Note*& notes, int& notesQuantity) {
    char buff[50];

    std::ifstream fin;
    fin.open("notes.txt");

    if (!fin.is_open()) return false;

    fin >> buff;
    notesQuantity = strtol(buff, nullptr, 10);

    notes = new Note[notesQuantity];

    for (int i = 0; i < notesQuantity; ++i) {
        for (int j = 0; j < 3; ++j) {
            fin >> buff;
            notes[i].name += buff;
            notes[i].name += " ";
        }

        fin >> buff;
        notes[i].phone = buff;

        fin >> buff;
        unsigned int day = strtol(buff, nullptr, 10);

        fin >> buff;
        unsigned int month = strtol(buff, nullptr, 10);

        fin >> buff;
        int year = strtol(buff, nullptr, 10);

        notes[i].birthday = {std::chrono::day{day}/std::chrono::month{month}/std::chrono::year{year}};
    }

    fin.close();

    return true;
}

Note findNote (Note* notes, int notesQuantity) {
    std::string targetPhone;
    std::cin >> targetPhone;

    for (int i = 0; i < notesQuantity; ++i) {
        if (notes[i].phone == targetPhone) {
            return notes[i];
        }
    }
    return {};
}

void printCountry (Note note, std::string * codes, int codesQuantity) {
    if (note.phone[0] - '0' < codesQuantity && note.phone[0] - '0' >= 0 && !codes[note.phone[0] - '0'].empty()) {
        std::cout << codes[note.phone[0] - '0'] << std::endl;
    } else {
        std::cout << "No such country!" << std::endl;
    }
}

void addNewNote (Note*& notes, int& notesQuantity, std::string * codes, int codesQuantity) {
    Note* newNotes = new Note[notesQuantity + 1];

    for (int i = 0; i < notesQuantity; ++i) {
        newNotes[i] = notes[i];
    }

    std::cout << "Enter firstname, patronymic and lastname: ";
    std::string firstname, patronymic, lastname;
    std::cin >> firstname >> patronymic >> lastname;
    newNotes[notesQuantity].name = firstname + " " + patronymic + " " + lastname;

    std::cout << std::endl << "Enter phone number without code: ";
    std::string number;
    std::cin >> number;

    std::cout << std::endl << "Enter birthday (day month year): ";
    std::string day, month, year;
    std::cin >> day >> month >> year;
    newNotes[notesQuantity].birthday = {std::chrono::day{(unsigned int) stoi(day)}/std::chrono::month{(unsigned int) stoi(month)}/std::chrono::year{stoi(year)}};

    std::cout << std::endl << "Select code" << std::endl;
    for (int i = 0; i < codesQuantity; ++i) {
        if (!codes[i].empty()) std::cout << i << " - " << codes[i] << std::endl;
    }
    std::string code;
    std::cin >> code;
    number = code + number;
    newNotes[notesQuantity].phone = number;

    delete[] notes;
    notes = newNotes;
    notesQuantity++;
}

void rewriteInput(Note* notes, int notesQuantity) {
    std::ofstream fout;
    fout.open ("notes.txt");

    fout << notesQuantity << std::endl;

    for (int i = 0; i < notesQuantity; ++i) {
        fout << notes[i].name << std::endl;
        fout << notes[i].phone << std::endl;
        fout << static_cast<unsigned>(notes[i].birthday.day()) << " " << static_cast<unsigned>(notes[i].birthday.month()) << " " << static_cast<int>(notes[i].birthday.year()) << std::endl;
    }


    fout.close();
}

int main() {
    int codesQuantity = 10;
    auto * codes = new std::string[codesQuantity];
    codes[1] = "North America";
    codes[2] = "Africa";
    codes[3] = "Europe 1";
    codes[4] = "Europe 2";
    codes[5] = "South America";
    codes[6] = "Oceania";
    codes[7] = "SNG";
    codes[8] = "Eastern Asia";
    codes[9] = "Western Asia";

    Note* notes;
    int notesQuantity;

    if (!readInput(notes, notesQuantity)) {
        std::cout << "File does not exist";
        return 1;
    }

    for (int i = 0; i < notesQuantity; ++i) {
        print(notes[i]);
    }

    Note foundNote = findNote(notes, notesQuantity);
    print(foundNote);
    printCountry(foundNote, codes, codesQuantity);

    addNewNote(notes, notesQuantity, codes, codesQuantity);

    rewriteInput(notes, notesQuantity);

    return 0;
}
