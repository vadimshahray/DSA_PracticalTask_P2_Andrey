#include <conio.h>
#include <stdio.h>
#include <windows.h>

const UCHAR N = 4; // Максимальное кол-во элементов в деке

enum COMMAND // Команды консольного меню
{
   PUSH,    // Добавить элемент в очередь
   POP,     // Вытолкнуть элемент из очереди
   EMPTY,   // Проверить, пуста ли очередь
   FULL,    // Проверить, полна ли очередь
   CLEAR,   // Очистить очередь
   PRINT,   // Вывести все элементы очереди на консоль
   EXIT     // Завершить выполнение программы
};


struct queue
{
   private:
   char beg = -1, end = -1, data[N] = { };

   public:
   /// <summary>
   /// Добавляет элемент e в конец очереди
   /// </summary>
   /// <param name="e">Элемент, который нужно добавить</param>
   /// <returns>Выполнилась ли операция</returns>
   bool push(char e)
   {
      bool is_f = full(), is_e = empty();
      if (!is_f)
      {
         end = is_e ? beg = 0 : end == N - 1 ? 0 : end + 1;
         data[end] = e;
      }

      return !is_f;
   }
   /// <summary>
   /// Выталкивет элемент из начала очереди и передает его в e
   /// </summary>
   /// <param name="e">Куда передать вытолкнутый элемент</param>
   /// <returns>Выполнилась ли операция</returns>
   bool pop(char &e)
   {
      bool is_e = empty(), will_e = beg == end;
      if (!is_e)
      {
         e = data[beg];
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
   void clear() { for (char e = 0; pop(e); ); }
   /// <summary>
   /// Выводит элементы очереди на консоль
   /// </summary>
   void print()
   {
      queue d;
      char e = 0;

      for (; pop(e); d.push(e)) printf_s("%c ", e);
      for (; d.pop(e); push(e));
   }
};


int main()
{
   UINT iCp = GetConsoleCP(), oCp = GetConsoleOutputCP();
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   queue q;
   char cmd, elem;
   bool repeat = true;
   do
   {
      printf_s("Выберите команду:\n[%d] Добавить элемент в очередь;\n[%d] Вытолкнуть элемент из очереди;\n[%d] Проверить, пуста ли очередь;\n[%d] Проверить, полна ли очередь;\n[%d] Очистить очередь;\n[%d] Вывести содержимое очереди;\n[%d] Завершить работу.\nКоманда: ",  PUSH, POP, EMPTY, FULL, CLEAR, PRINT, EXIT);

      scanf_s("\n%c", &cmd, 1);
      printf_s("\n");

      switch (cmd - '0')
      {
         case PUSH:
            printf_s("Введите элемент: ");
            scanf_s("\n%c", &elem, 1);

            printf_s(q.push(elem) ? "Элемент успешно добавлен."
                                  : "Не удалось добавить элемент: очередь полна."); break;
         case POP:
            q.pop(elem) ? printf_s("Вытолкнутый элемент: %c", elem)
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