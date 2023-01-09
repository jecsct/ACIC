int[] getLEDPins(int* outer_sem, int* inner_sem, int* ped_sem, int* power_pin, int* com_pin)
{

  int number_pins = 0;

  if( outer_sem != NULL)
  {
    number_pins = number_pins + 3;
  }
  if ( inner_sem != NULL)
  {
    number_pins = number_pins + 3;
  }
  if ( ped_sem != NULL )
  {
    number_pins = number_pins + 2;
  }
  if ( power_pin != NULL )
  {
    number_pins = number_pins + 1;
  }
  if ( com_pin != NULL )
  {
    number_pins = number_pins + 1;
  }

  int []returnArray = new int[number_pins];
  free(number_pins);

  int fill_indice = 0;

  if( outer_sem != NULL)
  {
    for ( int i = 0 ; i < 3 ; i++ )
    {
      returnArray[fill_indice] = outer_sem[i];
      fill_indice++;
    }
  }

  if( inner_sem != NULL)
  {
    for ( int i = 0 ; i < 3 ; i++ )
    {
      returnArray[fill_indice] = inner_sem[i];
      fill_indice++;
    }
  }

  if( ped_sem != NULL)
  {
    for ( int i = 0 ; i < 2 ; i++ )
    {
      returnArray[fill_indice] = ped_sem[i];
      fill_indice++;
    }
  }

  if( power_pin != NULL)
  {
    returnArray[fill_indice];
    fill_indice++;
  }

  if( com_pin != NULL)
  {
    returnArray[fill_indice];
    fill_indice++;
  }


  return {returnArray, fill_indice};
}