# include <iostream>
# include <stdio.h>
# include <vector> 
# include <stdlib.h> // atoi() 
# include <fstream> // writeOutput
using namespace std;
struct Data{
	int pageNum ;
	int counter ; // �ΦbLFU, MFU�W 
};
struct Node {
	int pageNum ;
	int counter ; // �ΦbLFU, MFU�W 
	vector<Data> pageFrame ; // �ثe��page frame(�[�J��(pageNum)���e) 
	string status ; // ����page Fault���p F: page fault, (�ť�) : �Lpage fault 
};



struct Info{
	int num_of_page_fault ;
	int num_of_replacement ;
	int num_of_page_frame ;
};
vector<Node> output_FIFO ; // ��X���F�賣�b�o�� FIFO
vector<Node> output_LRU ; // ��X���F�賣�b�o�� LRU
vector<Node> output_LFU ; // ��X���F�賣�b�o�� LFU
vector<Node> output_MFU ; // ��X���F�賣�b�o�� MFU
vector<Node> output_LFU_LRU ; // ��X���F�賣�b�o�� LFU_LRU
vector<Node> output_MFU_LRU ; // ��X���F�賣�b�o�� MFU_LRU
vector<Info> info ; // �C�@�����n��X�@�Ǹ�T�A�N�s�b�o��
 
bool ReadFile( string fileName, int &num_of_page_frame, vector<int> &list ) {
	FILE *pfile = NULL ;
	fileName = fileName + ".txt" ;
	pfile = fopen( fileName.c_str(), "r" ) ;
	if ( pfile == NULL ) {
		cout << "�ɮפ��s�b\n" ;
		return false ;
	} // if 
	else { // �}�lŪ�� 
		fscanf( pfile, "%d", &num_of_page_frame ) ; 
		char ch = '\0' ;
		fscanf( pfile, "%c", &ch ) ; // Ū���� 
		int pageNum  = 0 ;
		char str[2] = "\0" ;
		int temp = -1 ; // Ū�J���F��Ȧs
		while ( fscanf( pfile, "%c", &ch ) != EOF ) { // �@�Ӥ@��Ū�J�A�æs�Jlist(vector)�� 
			if ( ch != '\n' && ch != ' ' && ch != '\t' ) {
				str[0] = ch ;
				pageNum = atoi( str ) ;
				list.push_back( pageNum ) ;
			} // if 
			
		} // while
		  
		return true ;
	} // else 
} // ReadFile()

void WriteOutput( string fileName ) { // �L����(�g��) 
	fstream file ;
	int i = 0 ;
	int j = 0 ;
	string str = "out_" + fileName  ;
    str = str + ".txt"  ;
	file.open( str.c_str(), ios::out ) ;
	if( file ) {
		file << "--------------FIFO-----------------------" << "\n" ;
		i = 0 ;
		while ( i < output_FIFO.size() ) {
			Node n = output_FIFO.at(i) ; 
			file << n.pageNum << "	" ;
			j = 0 ;
			while ( j < n.pageFrame.size() ) {
				file << n.pageFrame.at(j).pageNum ;
				j++ ;
			} // while 
			
			if ( n.status == "F" ) {
				file << "	" << n.status ;
			} // if 
			
			file << "\n" ;
			i++ ;
		} // while 
		
		Info fifo = info.at(0) ; // FIFO
		file << "Page Fault = "<< fifo.num_of_page_fault << "  Page Replaces = " << fifo.num_of_replacement
		<< "  Page Frames = " << fifo.num_of_page_frame << "\n" ;
		// ---------------------------------------------------------------------------------------------------
		file << "\n" ;
		file << "--------------LRU-----------------------" << "\n" ;
		i = 0 ;
		while ( i < output_LRU.size() ) {
			Node n = output_LRU.at(i) ; 
			file << n.pageNum << "	" ;
			j = 0 ;
			while ( j < n.pageFrame.size() ) {
				file << n.pageFrame.at(j).pageNum  ;
				j++ ;
			} // while 
			
			if ( n.status == "F" ) {
				file << "	" << n.status ;
			} // if 
			
			file << "\n" ;
			i++ ;
		} // while 
		
		fifo = info.at(1) ; // LRU
		file << "Page Fault = "<< fifo.num_of_page_fault << "  Page Replaces = " << fifo.num_of_replacement
		<< "  Page Frames = " << fifo.num_of_page_frame << "\n" ;
		// ---------------------------------------------------------------------------------------------------
		file << "\n" ;
		file << "--------------Least Frequently Used Page Replacement-----------------------" << "\n" ;
		i = 0 ;
		while ( i < output_LFU.size() ) {
			Node n = output_LFU.at(i) ; 
			file << n.pageNum << "	" ;
			j = 0 ;
			while ( j < n.pageFrame.size() ) {
				file << n.pageFrame.at(j).pageNum  ;
				j++ ;
			} // while 
			
			if ( n.status == "F" ) {
				file << "	" << n.status ;
			} // if 
			
			file << "\n" ;
			i++ ;
		} // while 
		
		fifo = info.at(2) ; // LFU
		file << "Page Fault = "<< fifo.num_of_page_fault << "  Page Replaces = " << fifo.num_of_replacement
		<< "  Page Frames = " << fifo.num_of_page_frame << "\n" ;
		// ---------------------------------------------------------------------------------------------------
		file << "\n" ;
		file << "--------------Most Frequently Used Page Replacement -----------------------" << "\n" ;
		i = 0 ;
		while ( i < output_MFU.size() ) {
			Node n = output_MFU.at(i) ; 
			file << n.pageNum << "	" ;
			j = 0 ;
			while ( j < n.pageFrame.size() ) {
				file << n.pageFrame.at(j).pageNum  ;
				j++ ;
			} // while 
			
			if ( n.status == "F" ) {
				file << "	" << n.status ;
			} // if 
			
			file << "\n" ;
			i++ ;
		} // while 
		
		fifo = info.at(3) ; // MFU
		file << "Page Fault = "<< fifo.num_of_page_fault << "  Page Replaces = " << fifo.num_of_replacement
		<< "  Page Frames = " << fifo.num_of_page_frame << "\n" ;
		// ---------------------------------------------------------------------------------------------------
		// file << "\n" ;
		file << "--------------Least Frequently Used LRU Page Replacement-----------------------" << "\n" ;
		i = 0 ;
		while ( i < output_LFU_LRU.size() ) {
			Node n = output_LFU_LRU.at(i) ; 
			file << n.pageNum << "	" ;
			j = 0 ;
			while ( j < n.pageFrame.size() ) {
				file << n.pageFrame.at(j).pageNum  ;
				j++ ;
			} // while 
			
			if ( n.status == "F" ) {
				file << "	" << n.status ;
			} // if 
			
			file << "\n" ;
			i++ ;
		} // while 
		
		fifo = info.at(4) ; // LFU+LRU
		file << "Page Fault = "<< fifo.num_of_page_fault << "  Page Replaces = " << fifo.num_of_replacement
		<< "  Page Frames = " << fifo.num_of_page_frame << "\n" ;
		// ---------------------------------------------------------------------------------------------------
		file << "\n" ;
		file << "--------------Most Frequently Used LRU Page Replacement -----------------------" << "\n" ;
		i = 0 ;
		while ( i < output_MFU_LRU.size() ) {
			Node n = output_MFU_LRU.at(i) ; 
			file << n.pageNum << "	" ;
			j = 0 ;
			while ( j < n.pageFrame.size() ) {
				file << n.pageFrame.at(j).pageNum  ;
				j++ ;
			} // while 
			
			if ( n.status == "F" ) {
				file << "	" << n.status ;
			} // if 
			
			file << "\n" ;
			i++ ;
		} // while 
		
		fifo = info.at(5) ; // MFU+LRU
		file << "Page Fault = "<< fifo.num_of_page_fault << "  Page Replaces = " << fifo.num_of_replacement
		<< "  Page Frames = " << fifo.num_of_page_frame << "\n" ;
		
		
	} // if 
	
	
	file.close() ;
} // WriteOutput

bool IsInPageFrame( int pageNum, vector<Data> cur_page_frame ) { 
    // �P�_ pageNum �O�_�w�s�b�ثe�� page frame���F 
	int i = 0 ;
	while ( i < cur_page_frame.size() ) {
		if ( pageNum == cur_page_frame.at(i).pageNum ) { // �w�s�b 
			return true ;
		} // if 
		
		i++ ;
	} // while
	
	return false ; 
} // IsInPageFrame()

void FIFO( int size, vector<int> list ) { // ���i���X���m���k
    // size �� page frame ��size
    int num_of_page_fault = 0 ; // ����page fault����  
    int num_of_replacement = 0 ; // �O���m������ 
    output_FIFO.clear() ; // �����e�A����n��X�����ײM�� �H���U�@ 
    Node n ; // �F�賣�Ȧs�b�o�� 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // �o�]�O�Ȧs��page frame�ˤl 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // �n�]�Ҧ���page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // ���hcheck�O�_�w�s�b(�w�s�b���N���Υ[�J�s��pageNum)	 
		if ( cur_page_frame.size() == size && isExist == false ) { // �ثe�w�� (�B�n�[�J�s��page Num)
			cur_page_frame.erase( cur_page_frame.end()-1 ) ; // �R���̦��i�J�� 
			num_of_replacement++ ; // �m���@�� 
		} // if
		if ( isExist == false ) { // �u�n�٨S�s�b �N�i�H�[�J�s��pageNum 
			d.counter = 1 ;
			d.pageNum = n.pageNum ; 
			cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		} // if 
		
    	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // �N�ثepage frame���ˤl���s�_�� 
    	
    	 
    	if ( isExist ) { // �Y���w�s�bpage frame�� 
    		n.status = "" ; // �S��page fault �A�]���Χ��ثepage frame���ˤl 
		} // if 
		else {
			n.status = "F" ; // �o��page fault 			
			num_of_page_fault++ ; // ����page fault���� 
		} // else 
		
	    output_FIFO.push_back( n ) ;
	    
		i++ ;	 
	} // while 
 
    Info temp ;
    temp.num_of_page_fault = num_of_page_fault ;
    temp.num_of_page_frame = size ;
    temp.num_of_replacement = num_of_replacement ;
	info.push_back( temp ) ;
} // FIFO()

// ------------------------------------------------------------------------------------------------

void AdjustPageFrame( int pageNum, vector<Data> &cur_page_frame ) { // �վ�pageNum�b�ثepage frame����m 
	int i = 0 ;
	while ( i < cur_page_frame.size() ) { // ����즹pageNum�b���̡A���R���A�A���J�̫e�� 
		if ( pageNum == cur_page_frame.at(i).pageNum ) {
			cur_page_frame.erase( cur_page_frame.begin() + i ) ;
			break ; // ����! ���X�^�� 
		} // if 
		
		i++ ;
	} // while 
} // AdjustPageFrame()


void LRU( int size, vector<int> list ) { // �̪�u�έ��m���k 
	// size �� page frame ��size
    int num_of_page_fault = 0 ; // ����page fault����  
    int num_of_replacement = 0 ; // �O���m������ 
    output_LRU.clear() ; // �����e�A����n��X�����ײM�� �H���U�@ 
    Node n ; // �F�賣�Ȧs�b�o�� 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // �o�]�O�Ȧs��page frame�ˤl 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // �n�]�Ҧ���page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // ���hcheck�O�_�w�s�b(�w�s�b���N���Υ[�J�s��pageNum)
			 
		if ( cur_page_frame.size() == size ) { // �ثe�w�� (�B�n�[�J�s��page Num)
			if ( isExist == false ) {
				num_of_replacement++ ; // �m���@�� 	
				cur_page_frame.erase( cur_page_frame.end()-1 ) ; // �R���̦��i�J�� 	
				n.status = "F" ; // �o��page fault 			
				num_of_page_fault++ ; // ����page fault���� 
			} // if 
			else { // �w���s�b ���n�R�̦��i�J���A�ӬO���m�Y�i
				n.status = "" ; // �S��page fault �A�]���Χ��ثepage frame���ˤl 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; // �o�ӷ|�R��pageNum�o��page�A���U�|insert��̫e��				
			} // else 
				
		} // if
		else {
			if ( isExist ) { // �Y���w�s�bpage frame�� 
	    		AdjustPageFrame( n.pageNum, cur_page_frame ) ; // �o�ӷ|�R��pageNum�o��page�A���U�|insert��̫e��
	    		n.status = "" ; // �S��page fault �A�]���Χ��ثepage frame���ˤl 
			} // if 
			else {
				n.status = "F" ; // �o��page fault 			
				num_of_page_fault++ ; // ����page fault���� 
			} // else 
		} // else 
			
		
		d.pageNum = n.pageNum ; 
		cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		
		  	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // �N�ثepage frame���ˤl���s�_�� 
    	
    	 
    	
		
	    output_LRU.push_back( n ) ;
	    
		i++ ;	 
	} // while 
 
    Info temp ;
    temp.num_of_page_fault = num_of_page_fault ;
    temp.num_of_page_frame = size ;
    temp.num_of_replacement = num_of_replacement ;
	info.push_back( temp ) ;
} // LRU 

// ------------------------------------------------------------------------------------------------
int Find_Least_Freq( vector<Data> cur_page_frame ) { // �d��page frame�� counter�ȳ̤p���H�A�æ^�Ǩ�index 
	int i = 0 ;
	int min = i ;
	while ( i < cur_page_frame.size() ) {
		// �Ycounter�ۦP�A�h�^�ǳ̦��i�J��page�A�]���ڱN�̷s����bpage frame���̫e���A
		// �ҥH �̦��i�J��page�|�b�̫᭱ => �ҥH�Ycounter�ۦP�A�]�n�洫�A�~��F��^�ǳ̦��i�J��page 
		if ( cur_page_frame.at(i).counter <= cur_page_frame.at(min).counter ) {
			min = i ;
		} // if 
		
		i++ ;
	} // while
	
	return min ; 
} // Find_Least_Freq()

int UpdateCounter( int pageNum, vector<Data> & cur_page_frame) { // ���pageNum�Ҧb��m�A�ñN��counter+1 
	int i = 0 ;
	while ( i < cur_page_frame.size() ) {
		if ( pageNum == cur_page_frame.at(i).pageNum ) {
			cur_page_frame.at(i).counter = cur_page_frame.at(i).counter + 1 ;
			break ; // ����! ���X�j�� 
		} // if 
		
		i++ ;
	} // while 
	
	return cur_page_frame.at(i).counter ;
} // UpdateCounter

void LFU( int size, vector<int> list ) { // �̤��`�ϥέ��m���k 
	// size �� page frame ��size
    int num_of_page_fault = 0 ; // ����page fault����  
    int num_of_replacement = 0 ; // �O���m������ 
    output_LFU.clear() ; // �����e�A����n��X�����ײM�� �H���U�@ 
    Node n ; // �F�賣�Ȧs�b�o�� 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // �o�]�O�Ȧs��page frame�ˤl 
    Data d ; // �Ȧs��pageNum & counter 
    int i = 0 ;
    while ( i < list.size() ) { // �n�]�Ҧ���page reference
    	n.pageNum = list.at(i) ;
    	
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // ���hcheck�O�_�w�s�b(�w�s�b���N���Υ[�J�s��pageNum)	 
		if ( cur_page_frame.size() == size && isExist == false ) { // �ثe�w�� (�B�n�[�J�s��page Num)
		
			// return the index of the node which has least counter value
			int index = Find_Least_Freq( cur_page_frame ) ; 
			cur_page_frame.erase( cur_page_frame.begin() + index ) ; // �R����counter�̤p��
			num_of_replacement++ ; // �m���@�� 
		} // if
		
		if ( isExist == false ) { // �u�n�٨S�s�b �N�i�H�[�J�s��pageNum  
			d.pageNum = n.pageNum ;
			d.counter = 1 ; // �Ĥ@���X�{ 
			cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		} // if 
		else { // �w�g���s�bpage frame�F �n��s�L��counter
			d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 			
		} // else 
		
    	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // �N�ثepage frame���ˤl���s�_�� 
    	
    	 
    	if ( isExist ) { // �Y���w�s�bpage frame�� 
    		n.status = "" ; // �S��page fault �A�]���Χ��ثepage frame���ˤl
		} // if 
		else {
			n.status = "F" ; // �o��page fault 			
			num_of_page_fault++ ; // ����page fault���� 
		} // else 
		
	    output_LFU.push_back( n ) ;
	    
		i++ ;	 
	} // while 
 
    Info temp ;
    temp.num_of_page_fault = num_of_page_fault ;
    temp.num_of_page_frame = size ;
    temp.num_of_replacement = num_of_replacement ;
	info.push_back( temp ) ;
} // LFU() 
//---------------------------------------------------------------------------------------
int Find_Most_Freq( vector<Data> cur_page_frame ) { // �d��page frame�� counter�ȳ̤p���H�A�æ^�Ǩ�index 
	int i = 0 ;
	int max = i ;
	while ( i < cur_page_frame.size() ) {
		// �Ycounter�ۦP�A�h�^�ǳ̦��i�J��page�A�]���ڱN�̷s����bpage frame���̫e���A
		// �ҥH �̦��i�J��page�|�b�̫᭱ => �ҥH�Ycounter�ۦP�A�]�n�洫�A�~��F��^�ǳ̦��i�J��page 
		if ( cur_page_frame.at(i).counter >= cur_page_frame.at(max).counter ) {
			max = i ;
		} // if 
		
		i++ ;
	} // while
	
	return max ; 
} // Find_Least_Freq()


void MFU( int size, vector<int> list ) { // �̤��`�ϥέ��m���k 
	// size �� page frame ��size
    int num_of_page_fault = 0 ; // ����page fault����  
    int num_of_replacement = 0 ; // �O���m������ 
    output_MFU.clear() ; // �����e�A����n��X�����ײM�� �H���U�@ 
    Node n ; // �F�賣�Ȧs�b�o�� 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // �o�]�O�Ȧs��page frame�ˤl 
    Data d ; // �Ȧs��pageNum & counter 
    int i = 0 ;
    while ( i < list.size() ) { // �n�]�Ҧ���page reference
    	n.pageNum = list.at(i) ;
    	
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // ���hcheck�O�_�w�s�b(�w�s�b���N���Υ[�J�s��pageNum)	 
		if ( cur_page_frame.size() == size && isExist == false ) { // �ثe�w�� (�B�n�[�J�s��page Num)
		
			// return the index of the node which has least counter value
			int index = Find_Most_Freq( cur_page_frame ) ; 
			cur_page_frame.erase( cur_page_frame.begin() + index ) ; // �R����counter�̤p��
			num_of_replacement++ ; // �m���@�� 
		} // if
		
		if ( isExist == false ) { // �u�n�٨S�s�b �N�i�H�[�J�s��pageNum  
			d.pageNum = n.pageNum ;
			d.counter = 1 ; // �Ĥ@���X�{ 
			cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		} // if 
		else { // �w�g���s�bpage frame�F �n��s�L��counter
			d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 			
		} // else 
		
    	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // �N�ثepage frame���ˤl���s�_�� 
    	
    	 
    	if ( isExist ) { // �Y���w�s�bpage frame�� 
    		n.status = "" ; // �S��page fault �A�]���Χ��ثepage frame���ˤl
		} // if 
		else {
			n.status = "F" ; // �o��page fault 			
			num_of_page_fault++ ; // ����page fault���� 
		} // else 
		
	    output_MFU.push_back( n ) ;
	    
		i++ ;	 
	} // while 
 
    Info temp ;
    temp.num_of_page_fault = num_of_page_fault ;
    temp.num_of_page_frame = size ;
    temp.num_of_replacement = num_of_replacement ;
	info.push_back( temp ) ;
} // MFU() 
// ------------------------------------------------------------------------------------- 
void LFU_LRU( int size, vector<int> list ) { // �̪�u�έ��m���k 
	// size �� page frame ��size
    int num_of_page_fault = 0 ; // ����page fault����  
    int num_of_replacement = 0 ; // �O���m������ 
    output_LFU_LRU.clear() ; // �����e�A����n��X�����ײM�� �H���U�@ 
    Node n ; // �F�賣�Ȧs�b�o�� 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // �o�]�O�Ȧs��page frame�ˤl 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // �n�]�Ҧ���page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // ���hcheck�O�_�w�s�b(�w�s�b���N���Υ[�J�s��pageNum)
		d.pageNum = n.pageNum ; 	 
		if ( cur_page_frame.size() == size ) { // �ثe�w�� (�B�n�[�J�s��page Num)
			int index = Find_Least_Freq( cur_page_frame ) ; 
			if ( isExist == false ) {
				d.counter = 1 ; // �Ĥ@���X�{ 
				num_of_replacement++ ; // �m���@�� 	
				cur_page_frame.erase( cur_page_frame.begin() + index ) ; // �R����counter�̤p��	
			} // if 
			else { // ���n�R�̦��i�J���A�ӬO���m�Y�i
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// �R���L�쥻����m�A�̫�Ainsert��̫᭱						
			} // else 							
		} // if
		else { // size�٦��Ŷ� 
			if ( isExist == false ) {
				d.counter = 1 ; // �Ĥ@���X�{ 
			} // if 
			else { // �w�X�{ 
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// �R���L�쥻����m�A�̫�Ainsert��̫᭱
			} // else 
		} // else 
		
		cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
				  	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // �N�ثepage frame���ˤl���s�_�� 
    	 	 
    	if ( isExist ) { // �Y���w�s�bpage frame�� 
    		n.status = "" ; // �S��page fault �A�]���Χ��ثepage frame���ˤl 
		} // if 
		else {
			n.status = "F" ; // �o��page fault 			
			num_of_page_fault++ ; // ����page fault���� 
		} // else 
		
	    output_LFU_LRU.push_back( n ) ;
	    
		i++ ;	 
	} // while 
 
    Info temp ;
    temp.num_of_page_fault = num_of_page_fault ;
    temp.num_of_page_frame = size ;
    temp.num_of_replacement = num_of_replacement ;
	info.push_back( temp ) ;
} // LFU_LRU 
// ------------------------------------------------------------------------------------
void MFU_LRU( int size, vector<int> list ) { // �̪�u�έ��m���k 
	// size �� page frame ��size
    int num_of_page_fault = 0 ; // ����page fault����  
    int num_of_replacement = 0 ; // �O���m������ 
    output_MFU_LRU.clear() ; // �����e�A����n��X�����ײM�� �H���U�@ 
    Node n ; // �F�賣�Ȧs�b�o�� 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // �o�]�O�Ȧs��page frame�ˤl 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // �n�]�Ҧ���page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // ���hcheck�O�_�w�s�b(�w�s�b���N���Υ[�J�s��pageNum)
		d.pageNum = n.pageNum ; 	 
		if ( cur_page_frame.size() == size ) { // �ثe�w�� (�B�n�[�J�s��page Num)
			int index = Find_Most_Freq( cur_page_frame ) ; 
			if ( isExist == false ) {
				d.counter = 1 ; // �Ĥ@���X�{ 
				num_of_replacement++ ; // �m���@�� 	
				cur_page_frame.erase( cur_page_frame.begin() + index ) ; // �R����counter�̤p��	
			} // if 
			else { // ���n�R�̦��i�J���A�ӬO���m�Y�i
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// �R���L�쥻����m�A�̫�Ainsert��̫᭱
						
			} // else 
							
		} // if
		else { // size�٦��Ŷ� 
			if ( isExist == false ) {
				d.counter = 1 ; // �Ĥ@���X�{ 
			} // if 
			else { // �w�X�{ 
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// �R���L�쥻����m�A�̫�Ainsert��̫᭱
			} // else 
		} // else 

		
		
		cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		
		  	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // �N�ثepage frame���ˤl���s�_�� 
    	
    	 
    	if ( isExist ) { // �Y���w�s�bpage frame�� 
    		n.status = "" ; // �S��page fault �A�]���Χ��ثepage frame���ˤl 
		} // if 
		else {
			n.status = "F" ; // �o��page fault 			
			num_of_page_fault++ ; // ����page fault���� 
		} // else 
		
	    output_MFU_LRU.push_back( n ) ;
	    
		i++ ;	 
	} // while 
 
    Info temp ;
    temp.num_of_page_fault = num_of_page_fault ;
    temp.num_of_page_frame = size ;
    temp.num_of_replacement = num_of_replacement ;
	info.push_back( temp ) ;
} // MFU_LRU 



// ------------------------------------------------------------------------------------- 
int main() {
	string input_file_name = "" ;
	cout << "�п�J�nŪ�J���ɮצW��: " ;
	cout << "\n" ;
	cin >> input_file_name ;
	bool is_method_six = false ;
	int num_of_page_frame = 0 ;
	vector<int> list ;
	
	while ( !ReadFile(input_file_name, num_of_page_frame, list ) ) {
		cout << "�п�J�nŪ�J���ɮצW��: " ;
		cin >> input_file_name ;
	} // while 
	
	
	vector<int> list_fifo, list_lru, list_lfu, list_mfu, list_ll, list_ml ;
	// �NŪ�J����ƭӽƻs�@�� 
	list_fifo.assign( list.begin(), list.end() ) ;
	list_lru.assign( list.begin(), list.end() ) ;
	list_lfu.assign( list.begin(), list.end() ) ;
	list_mfu.assign( list.begin(), list.end() ) ;
	list_ll.assign( list.begin(), list.end() ) ;
	list_ml.assign( list.begin(), list.end() ) ;
	// �|�Ψ쪺��num_of_page_frame ��list 
	FIFO( num_of_page_frame, list_fifo ) ; // ���i���X���m���k
	LRU( num_of_page_frame, list_lru ) ; // �̪�u�έ��m���k 
	LFU( num_of_page_frame, list_lfu ) ; // �̤��`�ϥέ��m���k 
	MFU( num_of_page_frame, list_mfu ) ; // �̱`�ϥέ��m���k 
	LFU_LRU( num_of_page_frame, list_ll ) ;
	MFU_LRU( num_of_page_frame, list_ml ) ;
	WriteOutput( input_file_name ) ;

	
	return 0;
}
