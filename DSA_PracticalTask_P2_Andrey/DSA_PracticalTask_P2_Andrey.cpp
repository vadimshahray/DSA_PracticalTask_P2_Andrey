#include <conio.h>
#include <stdio.h>
#include <windows.h>

const UCHAR N = 7; // Максимальное кол-во элементов в очереди

enum COMMAND // Команды консольного меню
{
   PUSH,     // Добавить элемент в очередь
   POP,      // Вытолкнуть элемент из очереди
   EMPTY,    // Проверить, пуста ли очередь
   FULL,     // Проверить, полна ли очередь
   CLEAR,    // Очистить очередь
   PRINT,    // Вывести все элементы очереди на консоль
   EXIT      // Завершить выполнение программы
};

struct item
{
   private:
   int priority;
   
   public:
   item(char _value = 0, int _priority = -1) : value(_value), priority(_priority) { }
   
   char value;
   
   int get_priority() { return priority; };
};

struct queue
{
   private:
   char beg = -1, end = -1;
   item data[N] = { };

   public:
   /// <summary>
   /// Добавляет элемент item в конец очереди
   /// </summary>
   /// <param name="i">Элемент, который нужно добавить</param>
   /// <returns>Выполнилась ли операция</returns>
   bool push(item i)
   {
      bool is_f = full(), is_e = empty();
      if (!is_f)
      {
         char p = beg;
         for ( ; data[p].get_priority() <= i.get_priority() && p != end + 1; p == N - 1 && p != end ? p = 0 : p++);
         for (char j = end == N - 1 ? 0 : end; j != p - 1; j == 0 && j != p ? j = N - 1 : j--)
            data[j + 1] = data[j];

         data[p] = i;
         end = is_e ? beg = 0 : end == N - 1 ? 0 : end + 1;
      }

      return !is_f;
   }
   /// <summary>
   /// Выталкивет элемент из начала очереди и передает его в item
   /// </summary>
   /// <param name="i">Куда передать вытолкнутый элемент</param>
   /// <returns>Выполнилась ли операция</returns>
   bool pop(item &i)
   {
      bool is_e = empty(), will_e = beg == end;
      if (!is_e)
      {
         i = data[beg];
         beg = will_e ? end = -1 : beg == N - 1 ? 0 : beg + 1;
      }

      return !is_e;
   }

   /// <summary>
   /// Проверяет, пуста ли очередь
   /// </summary>
   bool empty() { return beg == -1; }
   /// <summary>
   /// Проверяет, полна ли очередь
   /// </summary>
   bool full() { return beg - end == 1 || end - beg == N - 1; }

   /// <summary>
   /// Очищает очередь
   /// </summary>
   void clear() { for (item i = 0; pop(i); ); }
   /// <summary>
   /// Выводит элементы очереди на консоль
   /// </summary>
   void print()
   {
      queue d;
      item i = 0;

      for ( ; pop(i); d.push(i)) printf_s("%c ", i.value);
      for ( ; d.pop(i); push(i));
   }
};


int main()
{
   UINT iCp = GetConsoleCP(), oCp = GetConsoleOutputCP();
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   item i;
   queue q;
   int p;
   char cmd, v;
   bool repeat = true;
   do
   {
      printf_s("Выберите команду:\n"
               "[%d] Добавить элемент в очередь;\n"
               "[%d] Вытолкнуть элемент из очереди;\n"
               "[%d] Проверить, пуста ли очередь;\n"
               "[%d] Проверить, полна ли очередь;\n"
               "[%d] Очистить очередь;\n"
               "[%d] Вывести содержимое очереди;\n"
               "[%d] Завершить работу.\n"
               "Команда: ", PUSH, POP, EMPTY, FULL, CLEAR, PRINT, EXIT);

      scanf_s("\n%c", &cmd, 1);
      printf_s("\n");

      switch (cmd - '0')
      {
         case PUSH:
            printf_s("Введите элемент: ");
            scanf_s("\n%c", &v, 1);
            printf_s("Укажите его приоритет: ");
            scanf_s("\n%d", &p); 

            printf_s(q.push(item(v, p)) ? "Элемент успешно добавлен."
                                        : "Не удалось добавить элемент: очередь полна."); break;
         case POP:
            q.pop(i) ? printf_s("Вытолкнутый элемент: %c", i.value)
                        : printf_s("Не удалось выполнить данную операцию: очередь пуста."); break;
         case EMPTY:
            printf_s(q.empty() ? "Очередь пуста." : "Очередь не пуста."); break;
         case FULL:
            printf_s(q.full() ? "Очередь полна." : "Очередь не полна."); break;
         case CLEAR:
            q.clear();
            printf_s("Очередь очищена."); break;
         case PRINT:
            printf_s("Содержимое очереди:\n");
            q.print(); break;
         case EXIT:
            repeat = false; break;
         default:
            printf_s("Неверный номер команды."); break;
      }
      printf_s("\n\n");
   } while (repeat);

   SetConsoleCP(iCp);
   SetConsoleOutputCP(oCp);

   return 0 * _getch();
}