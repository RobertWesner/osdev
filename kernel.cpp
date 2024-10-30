void print()
{
    char* video_memory = (char*) 0xb8000;

    // Create a pointer to a char , and point it to the first text cell of
    // video memory ( i . e . the top - left of the screen )
    // At the address pointed to by video_memory , store the character ’X ’
    // ( i . e . display ’X ’ in the top - left of the screen ).
    *video_memory = 'X';
}

int main ()
{
  print();
}