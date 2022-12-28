#include <ExtraX/Mathematics.h>


using namespace ExtraX;
using namespace ExtraX::Mathematics;

int main()
{
	Quaternion color = {1.0f,2.0f,3.0f,4.0f};
	
	std::cout << color.x<<" " << color.y << " " << color.z << " " << color.w << " ";
}