#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int processSize, processRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
	MPI_Comm_size(MPI_COMM_WORLD, &processSize);
	int mg;
	if(processRank != 0){
		MPI_Recv(&mg,1,MPI_INT,processRank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout<<"Process "<<processRank<<" received $ "<< mg<<" from process "<<processRank-1<<endl;
	}
	else{
		mg = 1000;
	}
	MPI_Send(&mg,1, MPI_INT,(processRank+1)%processSize,0,MPI_COMM_WORLD);
	if(processRank == 0){
		MPI_Recv(&mg,1,MPI_INT,processSize-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout<<"Process "<<processRank<<" received $ "<< mg<<" from process "<<processSize-1<<endl;
	}
	MPI_Finalize();
	return 0;
}
