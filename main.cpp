#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDate>


class Currency {
public:

    QString name1;
    QString name2;

    float course;
    QDate date;

};

// Проверяет, является ли строка s датой, и если да - преобразует ее в объект QDate

bool isDate(const QString& dateStr, QDate& date) {
    date = QDate::fromString(dateStr, "dd.MM.yyyy");
    return date.isValid();
}

// Проверяет, является ли строка s числом с плавающей точкой и, если да - преобразует ее в тип float
bool isFloat(const QString& s, float& num) {
    bool ok;
    // Преобразует строку в тип float и устанавливает флаг ok в true, если преобразование прошло успешно
    num = s.toFloat(&ok);
    return ok; // Возвращает true, если преобразование строки в тип float прошло успешно
}


int main()
{
    QFile file("in.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file); // Создаем объект QTextStream для чтения данных из файла построчно

        // В цикле читаем строки из файла
        while (!in.atEnd()) {
            QString line = in.readLine(); // Читаем строку из файла
            QStringList parts = line.split(" "); // Разделяем строку на подстроки по пробелам

            Currency curr; // Создаем объект класса "currency"

            for (const QString& part : parts) {
                float num;
                QDate dt;

                // Проверяем, является ли подстрока числом с плавающей точкой
                if (isFloat(part, num)) {
                    curr.course = num; // Если да, сохраняем это число в поле "course" объекта "currency"

                }
                else if (isDate(part, dt)) { // Если подстрока является датой
                    curr.date = dt;
                }
                else {
                    // Отделяем другие части строки, которые могут быть названиями валют
                    if (curr.name1.isEmpty())
                        curr.name1 = part;
                    else if (curr.name2.isEmpty())
                        curr.name2 = part;
                }
            }

            qDebug() << "Валюта 1:" << curr.name1 << "Валюта 2:" << curr.name2 << "Курс:" << curr.course << "Дата:" << curr.date.toString("yyyy.MM.dd");
        }

    }
    else {
        qDebug() << "Не удалось открыть файл";
    }

    return 0;
}
