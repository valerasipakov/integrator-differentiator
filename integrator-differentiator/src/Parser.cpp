#include"Parser.h"



const double Pi = acos(-1);

double parser::calculate(std::string str)
{

    std::stringstream sstr{ str };
    char Ch; //����������, � ������� ����� ������������ ������� �������������� ������
    double value;
    bool flag = true; //����� ��� ����, ����� ��������� ������ �������� ������� ����� (-5) �� ��������� (2-5)
    std::stack<Leksema> Stack_n; //���� � �������
    std::stack<Leksema> Stack_o; //���� � ����������
    Leksema item = Leksema(); //������ ���� Leksema
    while (true) {
        Ch = sstr.peek(); //������� �� ������ ������
        if (Ch == '\377')break; //���� ��������� ����� ������, ������� �� �����
        if (Ch == ' ') { //������������� ��������
            sstr.ignore();
            continue;
        }
        if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e' || Ch == 'l') { //���� ��������� �������
            char foo[3]; //������ �� 3 ������� ��� ����������� ���� ����������� �������
            for (int i = 0; i < 3; i++) {
                Ch = sstr.peek();
                foo[i] = Ch;
                sstr.ignore();
            }
            if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') { //���� ����������� ������� - �����
                changeLeksema(item, 's', 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') { //���� ����������� ������� - �������
                changeLeksema(item, 'c', 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                continue;
            }
            if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') { //���� ����������� ������� - �������
                changeLeksema(item, 't', 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') { //���� ����������� ������� - ���������
                changeLeksema(item, 'g', 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                continue;
            }
            if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') { //���� ����������� ������� - ����������
                changeLeksema(item, 'e', 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                continue;
            }
            if (foo[0] == 'l' && foo[1] == 'o' && foo[2] == 'g') { //���� ����������� ������� - ��������
                changeLeksema(item, 'l', 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                continue;
            }
        }
        if (Ch == 'p') { //���� ��������� ����� ��
            changeLeksema(item, '0', Pi);
            Stack_n.push(item); //����� �������� � ���� � �������
            flag = 0;
            sstr.ignore();
            continue;
        }
        if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //���� ��������� �����
            sstr >> value;
            changeLeksema(item, '0', value);
            Stack_n.push(item); //����� �������� � ���� � �������
            flag = 0;
            continue;
        }
        if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') { //���� ��������� ��������
            if (Stack_o.size() == 0) { //���� ���� � ���������� ����
                changeLeksema(item, Ch, 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                sstr.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && getRang(Ch) >
                getRang(Stack_o.top().type)) { //���� ���� � ���������� �� ����, �� ��������� ������� �������� ���� ������� � ����� � ����������
                changeLeksema(item, Ch, 0);
                Stack_o.push(item); //�������� �������� � ���� � ����������
                sstr.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && getRang(Ch) <=
                getRang(Stack_o.top().type)) {//���� ���� � ���������� �� ����, �� ��������� ������� �������� ���� ���� ����� ������� � ����� � ���������
                Maths(Stack_n, Stack_o, item);
                continue;
            }
        }
        if (Ch == '(') { //���� ��������� ������������� ������
            changeLeksema(item, Ch, 0);
            Stack_o.push(item); //�������� �������� � ���� � ����������
            sstr.ignore();
            flag = 1; // ��� ����, ����� �������� 4*(-5) �� 4-5
            continue;
        }
        if (Ch == ')') { //���� ��������� ������������� ������
            while (Stack_o.top().type != '(') {
                Maths(Stack_n, Stack_o, item);
                continue;
            }
            Stack_o.pop();
            sstr.ignore();
            continue;
        }
        else { //���� �������� �����-�� �������� ������
            std::cout << "\nExpression entered incorrectly\n";
            system("pause");
            return 0;
        }
    }
    while (Stack_o.size() != 0) { //�������� �����. ������� �� ��� ���, ���� � ����� � ���������� �� ����� 0 ���������
        Maths(Stack_n, Stack_o, item);
        continue; //���� ��� ������
    }
    return Stack_n.top().value;
    system("pause");
}

double parser::Sin(double x) { //������� ��� ���������� �������� ������
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

void parser::changeLeksema(Leksema& leksema, char type, double value) {
    leksema.type = type;
    leksema.value = value;
}

void parser::Maths(std::stack<Leksema>& Stack_n, std::stack<Leksema>& Stack_o, Leksema& item)
{
    double a, b, c;
    a = Stack_n.top().value; //������� ������� ����� �� ����� � �������
    Stack_n.pop(); //��������� ������� ����� �� ����� � �������
    switch (Stack_o.top().type) {  //����������� ��� ������� �������� �� ����� � ����������
    case '+': //���� ��� ������� �������� �� ����� � ���������� ��������
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a + b;
        changeLeksema(item, '0', c);
        Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
        Stack_o.pop();
        break;

    case '-':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = b - a;
        changeLeksema(item, '0', c);
        Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
        Stack_o.pop();
        break;

    case '^':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = pow(b, a);
        changeLeksema(item, '0', c);
        Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
        Stack_o.pop();
        break;

    case '*':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a * b;
        changeLeksema(item, '0', c);
        Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
        Stack_o.pop();
        break;

    case '/':
        b = Stack_n.top().value;
        if (a != 0) {

            Stack_n.pop();
            c = (b / a);
            changeLeksema(item, '0', c);
            Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
            Stack_o.pop();
            break;
        }
        else {
            throw std::invalid_argument("Division by zero");
        }

    case 's':
        c = Sin(a);
        changeLeksema(item, '0', c);
        Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
        Stack_o.pop();
        break;

    case 'c':
        c = Cos(a);
        changeLeksema(item, '0', c);
        Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
        Stack_o.pop();
        break;

    case 't':

        if (Cos(a) != 0) {
            c = tan(a);
            changeLeksema(item, '0', c);
            Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
            Stack_o.pop();
            break;
        }
        else {
            throw std::invalid_argument("tg is not defined");
        }

    case 'g':
        if (Sin(a) != 0) {
            c = Ctg(a);
            changeLeksema(item, '0', c);
            Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
            Stack_o.pop();
            break;


        }
        else {
            throw std::invalid_argument("ctg is not defined");
        }

    case 'e':
        c = exp(a);
        changeLeksema(item, '0', c);
        Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
        Stack_o.pop();
        break;

    case 'l':
        if (a > 0) {
            c = log(a);
            changeLeksema(item, '0', c);
            Stack_n.push(item); //��������� �������� �������� ������� � ���� � �������
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
