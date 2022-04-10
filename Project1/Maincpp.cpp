#include"Header.h"


int main() {
	system("mode con cols=134 lines=40");
	srand(time(0));
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	STUDENT Mass;
	Mass.count = 0;
	Mass.mass = NULL;
	Mass.GroupeNumberSort = false;
	SetCustomization();
	/*SetCustomization();
	Array mass;
	mass.Size = 0;
	mass.Array = NULL;
	mass.sort = false;*/

	while (true) {
		menu();

		pointer(&Mass);
	}
	return 0;
}