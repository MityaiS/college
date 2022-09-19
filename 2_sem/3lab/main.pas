
Program Lab3;

{$MODE DELPHI}

Uses 
SysUtils,
UnList,
Unvar;

Procedure AddR(Var ListN, ListK: PElem; r: String);

Var 
  len1, len2: integer;
  ListC: PElem;
Begin
  len1 := length(r);
  If ListN = Nil Then CreateList(ListN, ListK, r)
  Else
    Begin
      len2 := length(ListN^.info);
      If len2>=len1 Then AddFirst(ListN, ListK, r)
      Else
        Begin
          len2 := length(ListK^.info);
          If len2<=len1 Then AddLast(ListN, ListK, r)
          Else
            Begin
              len2 := 0;
              ListC := ListN;
              While (len1>=len2) Do
                Begin
                  ListC := ListC^.next;
                  len2 := length(ListC^.info);
                End;
              AddMedium(ListN, ListC^.prev, ListK, r)
            End;
        End;
    End;
End;

Procedure AddN;

Var n,i: integer;
  s: string;
  r: string;
  y: integer;
Begin
  write('Сколько N=?');
  readln(s);
  While Not TryStrToInt(s,n) Do
    Begin
      write('Некорректная N. Повторите еще раз: ');
      readln(s);
    End;
  For i:=1 To n Do
    Begin
      y := Random(9);
      getc(y,r);
      AddR(NachaloSpiska, KonecSpiska, r);
    End;
End;

Procedure AddFromTextFile;

Var 
  f: TextFile;
  c: string;
Begin
  If ParamCount=0 Then writeln('Вы не указали файл!')
  Else
    Begin
      AssignFile(f, ParamStr(1));
      Try
        Reset(f);
        Try
          While Not eof(f) Do
            Begin
              readln(f, c);
              AddR(NachaloSpiska, KonecSpiska, c);
            End;
          writeln('Список создан');
        Finally
          CloseFile(f);
    End;
Except
  writeln('Не удалось открыть текстовый файл '+
          ParamStr(1));
End;
End;
End;

Procedure Add1;

Var 
  c: string;
Begin
  write('введите страну ');
  readln(c);
  AddR(NachaloSpiska, KonecSpiska, c);
End;

Procedure SearchIt;

Var 
  ListC: PElem;
  flag: boolean;
  ch: integer;
  pe: string;
Begin
  flag := false;
  ListC := NachaloSpiska;
  ch := 0;

  While (ListC<>Nil) And (flag=false) Do
    Begin
      pe := copy(ListC^.info,1,1);
      If (pe='A') Or (pe='a') Then
        Begin
          Writeln(ListC^.info,' в ячейке ', ch+1);
          flag := true;
        End;
      ListC := ListC^.next;
      ch := ch+1;
    End;
  If flag=false Then writeln('Не найдено');
End;

Procedure ViewList;

Var 
  ListC: PElem;
Begin
  writeln('Список:');
  ListC := NachaloSpiska;
  If ListC=Nil Then writeln('Пустой');

  While ListC<>Nil Do
    Begin
      writeln(ListC.info);
      ListC := ListC^.next;
    End;
  writeln('Список в обратном порядке:');
  ListC := KonecSpiska;
  While ListC<>Nil Do
    Begin
      writeln(ListC.info);
      ListC := ListC^.prev;
    End;
End;

Var 
  ch: char;
Begin

  Randomize;

  Repeat
    writeln('--------------------------------------');
    writeln(

   'Q - добавить в список из текстового файла; '
    );
    writeln(

          'W - сгенерировать и добавить в список; '
    );
    writeln('E - добавить в список; ');
    writeln('R - найти в списке;');
    writeln('T - удалить(очистить) список;');
    writeln('Y - просмотр;');
    writeln('U - конец.');
    write('Ваш выбор?');
    readln(ch);
    writeln('--------------------------------------');

    ch := UpCase(ch);
    Case ch Of 
      'Q': AddFromTextFile;
      'W': AddN;
      'E': Add1;
      'R': SearchIt;
      'T': FreeList(NachaloSpiska, KonecSpiska);
      'Y': ViewList;
      'U': exit;
      Else
        Begin
          writeln('Нет такой команды');
          write('Press ENTER');
          readln;
        End;
    End;

  Until ch='U';
End.
