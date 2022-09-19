
Unit UnList;
{$MODE DELPHI}

Interface

Type 
  TInfo = (Ukrain , Belarus , USA ,  UK, Ireland, Spain, Litva, Iran, Argentina)
  ;

  PElem = ^TElem;
  TElem = Record
    info: string;
    next: PElem;
    prev: PElem;
  End;

Procedure CreateList(Var ListN, ListK: PElem; r: String);
Procedure AddFirst(Var ListN: PElem; ListK: PElem; r: String);
Procedure AddLast(ListN: PElem; Var ListK: PElem; r: String);
Procedure AddMedium(ListN,ListC,ListK: PElem; r: String);
Procedure FreeList(Var ListN, ListK: PElem);
Procedure getc(Var g:integer; Var s:String);

Implementation

Procedure CreateList(Var ListN, ListK: PElem; r: String);
Begin
  New(ListN);
  ListK := ListN;
  ListN^.info := r;
  ListN^.next := Nil;
  ListN^.prev := Nil;
End;

Procedure AddFirst(Var ListN: PElem; ListK: PElem; r: String);

Var Elem: PElem;
Begin
  new(Elem);
  Elem^.info := r;
  Elem^.next := ListN;
  Elem^.next^.prev := Elem;
  ListN := Elem;
  Elem^.prev := Nil;
End;

Procedure getc(Var g:integer; Var s:String);
Begin
  Case g Of 
    0: s := 'Ukrain';
    1: s := 'Belarus';
    2: s := 'USA';
    3: s := 'UK';
    4: s := 'Ireland';
    5: s := 'Spain';
    6: s := 'Litva';
    7: s := 'Iran';
    8: s := 'Argentina';
  End;
End;


Procedure AddLast(ListN: PElem; Var ListK: PElem; r: String);

Var Elem: PElem;
Begin
  new(elem);
  Elem^.info := r;
  ListK^.next := Elem;
  Elem^.prev := ListK;
  ListK := ListK^.next;
  Elem^.next := Nil;
End;


Procedure AddMedium(ListN,ListC,ListK: PElem; r: String);

Var Elem: PElem;
Begin
  new(Elem);
  Elem^.info := r;
  Elem^.next := ListC^.next;
  Elem^.prev := ListC;
  ListC^.next^.prev := Elem;
  ListC^.next := Elem;
End;

Procedure FreeList(Var ListN, ListK: PElem);

Var Elem: PElem;
Begin
  Elem := ListN;
  While Elem<>Nil Do
    Begin
      ListN := ListN^.next;
      Dispose(Elem);
      Elem := ListN;
    End;
  ListK := Nil;
End;

End.
