
void main()
{
	int i = 0;
	while(true){
		Move(DOWN);
		Move(RIGHT);
		Move(UP);
		Move(LEFT);
		if((i % 5) == 0){
			Sleep(20);
		}
		i++;
	}
}