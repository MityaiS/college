
Program Educational_practicу;

Const 
  Nmax = 20;

//ограничение максимального количества элементов в массиве

Var 
  n,i,min: integer;
  A: array[1..Nmax] Of integer;
  fin, fout: TextFile;

Begin

//связывание файловых переменных с внешними файлами
  Assign(fout,'br.txt');
  Assign(fin,'ar.txt');

  Reset(fin);

//открытие уже существующего файла(если файла с таким именем не существует, то возникнет ошибка)
  Rewrite(fout);

//создание нового файла(если файл с таким названием уже существует, то он пересоздается)

  readln(fin, n);
  //количество элементов в массиве
  For i:=1 To n Do
    read(fin,A[i]);
  //считывание массива
  min := a[1];
  For i:=1 To n Do
    Begin
      If a[i]<min Then
        Begin
          min := a[i];
        End;
    End;

  writeln(fout,
   'наименьший элемент одномерного массива: '
  );
  writeln(fout,' ', min);
  Close(fin);
  Close(fout);
  write('Нажмите Enter');
  readln;
End.
