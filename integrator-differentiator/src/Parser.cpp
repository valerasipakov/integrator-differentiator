#include"Parser.h"



const double Pi = acos(-1);

double parser::calculate(std::string str)
{

    std::stringstream sstr{ str };
    char Ch; //Переменная, в которую будет записываться текущий обрабатываемый символ
    double value;
    bool flag = true; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)
    std::stack<Leksema> Stack_n; //Стек с числами
    std::stack<Leksema> Stack_o; //Стек с операциями
    Leksema item = Leksema(); //Объект типа Leksema
    while (true) {
        Ch = sstr.peek(); //Смотрим на первый символ
        if (Ch == '\377')break; //Если достигнут конец строки, выходим из цикла
        if (Ch == ' ') { //Игнорирование пробелов
            sstr.ignore();
            continue;
        }
        if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e' || Ch == 'l') { //Если прочитана функция
            char foo[3]; //массив на 3 символа для определения типа прочитанной функции
            for (int i = 0; i < 3; i++) {
                Ch = sstr.peek();
                foo[i] = Ch;
                sstr.ignore();
            }
            if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') { //Если прочитанная функция - синус
                item.type = 's';
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') { //Если прочитанная функция - косинус
                item.type = 'c';
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                continue;
            }
            if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') { //Если прочитанная функция - тангенс
                item.type = 't';
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') { //Если прочитанная функция - котангенс
                item.type = 'g';
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                continue;
            }
            if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') { //Если прочитанная функция - экспонента
                item.type = 'e';
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                continue;
            }
            if (foo[0] == 'l' && foo[1] == 'o' && foo[2] == 'g') { //Если прочитанная функция - логарифм
                item.type = 'l';
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                continue;
            }
        }
        if (Ch == 'p') { //Если прочитано число Пи
            item.type = '0';
            item.value = Pi;
            Stack_n.push(item); //Число кладется в стек с числами
            flag = 0;
            sstr.ignore();
            continue;
        }
        if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //Если прочитано число
            sstr >> value;
            item.type = '0';
            item.value = value;
            Stack_n.push(item); //Число кладется в стек с числами
            flag = 0;
            continue;
        }
        if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') { //Если прочитана операция
            if (Stack_o.size() == 0) { //Если стек с операциями пуст
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                sstr.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && getRang(Ch) >
                getRang(Stack_o.top().type)) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                sstr.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && getRang(Ch) <=
                getRang(Stack_o.top().type)) {//Если стек с операциями НЕ пуст, но приоритет текущей операции ниже либо равен верхней в стеке с операциям
                Maths(Stack_n, Stack_o, item);
                continue;
            }
        }
        if (Ch == '(') { //Если прочитана открывающаяся скобка
            item.type = Ch;
            item.value = 0;
            Stack_o.push(item); //Операция кладется в стек с операциями
            sstr.ignore();
            flag = 1; // для того, чтобы отличить 4*(-5) от 4-5
            continue;
        }
        if (Ch == ')') { //Если прочитана закрывающаяся скобка
            while (Stack_o.top().type != '(') {
                Maths(Stack_n, Stack_o, item);
                continue;
            }
            Stack_o.pop();
            sstr.ignore();
            continue;
        }
        else { //Если прочитан какой-то странный символ
            std::cout << "\nНеверно введено выражение!\n";
            system("pause");
            return 0;
        }
    }
    while (Stack_o.size() != 0) { //Вызываем матем. функцию до тех пор, пока в стеке с операциями не будет 0 элементов
        Maths(Stack_n, Stack_o, item);
        continue; //Если все хорошо
    }
    return Stack_n.top().value;
    system("pause");
}

double parser::Sin(double x) { //Функция для округления значение синуса
    return (round(sin(x) * 10000000) / 10000000);
}

double parser::Cos(double x)
{
    return (round(cos(x) * 10000000) / 10000000);
}

double parser::Ctg(double x)
{
    double a = cos(x);
    double b = Sin(x);
    return (a / b);
}

int parser::getRang(char ch)
{
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g' || ch == 'e' || ch == 'l')return 4;
    if (ch == '^')return 3;
    if (ch == '+' || ch == '-')return 1;
    if (ch == '*' || ch == '/')return 2;
    else return 0;
}



void parser::Maths(std::stack<Leksema>& Stack_n, std::stack<Leksema>& Stack_o, Leksema& item)
{
    double a, b, c;
    a = Stack_n.top().value; //Берется верхнее число из стека с числами
    Stack_n.pop(); //Удаляется верхнее число из стека с числами
    switch (Stack_o.top().type) {  //Проверяется тип верхней операции из стека с операциями
    case '+': //Если тип верхней операции из стека с операциями сложение
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a + b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case '-':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case '^':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = pow(b, a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case '*':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case '/':
        b = Stack_n.top().value;
        if (a != 0) {

            Stack_n.pop();
            c = (b / a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item); //Результат операции кладется обратно в стек с числами
            Stack_o.pop();
            break;
        }
        else {
            throw std::invalid_argument("Division by zero");
        }

    case 's':
        c = Sin(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case 'c':
        c = Cos(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case 't':

        if (Cos(a) != 0) {
            c = tan(a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item); //Результат операции кладется обратно в стек с числами
            Stack_o.pop();
            break;
        }
        else {
            throw std::invalid_argument("tg is not defined");
        }

    case 'g':
        if (Sin(a) != 0) {
            c = Ctg(a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item); //Результат операции кладется обратно в стек с числами
            Stack_o.pop();
            break;


        }
        else {
            throw std::invalid_argument("ctg is not defined");
        }

    case 'e':
        c = exp(a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case 'l':
        if (a > 0) {
            c = log(a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item); //Результат операции кладется обратно в стек с числами
            Stack_o.pop();
            break;
        }
        else
        {
            throw std::invalid_argument("log is not defined");
        }
    default:
        throw std::invalid_argument("Unexepted error");
    }
}
