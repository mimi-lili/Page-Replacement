# include <iostream>
# include <stdio.h>
# include <vector> 
# include <stdlib.h> // atoi() 
# include <fstream> // writeOutput
using namespace std;
struct Data{
	int pageNum ;
	int counter ; // 用在LFU, MFU上 
};
struct Node {
	int pageNum ;
	int counter ; // 用在LFU, MFU上 
	vector<Data> pageFrame ; // 目前的page frame(加入此(pageNum)之前) 
	string status ; // 紀錄page Fault狀況 F: page fault, (空白) : 無page fault 
};



struct Info{
	int num_of_page_fault ;
	int num_of_replacement ;
	int num_of_page_frame ;
};
vector<Node> output_FIFO ; // 輸出的東西都在這裡 FIFO
vector<Node> output_LRU ; // 輸出的東西都在這裡 LRU
vector<Node> output_LFU ; // 輸出的東西都在這裡 LFU
vector<Node> output_MFU ; // 輸出的東西都在這裡 MFU
vector<Node> output_LFU_LRU ; // 輸出的東西都在這裡 LFU_LRU
vector<Node> output_MFU_LRU ; // 輸出的東西都在這裡 MFU_LRU
vector<Info> info ; // 每一項都要輸出一些資訊，就存在這裡
 
bool ReadFile( string fileName, int &num_of_page_frame, vector<int> &list ) {
	FILE *pfile = NULL ;
	fileName = fileName + ".txt" ;
	pfile = fopen( fileName.c_str(), "r" ) ;
	if ( pfile == NULL ) {
		cout << "檔案不存在\n" ;
		return false ;
	} // if 
	else { // 開始讀檔 
		fscanf( pfile, "%d", &num_of_page_frame ) ; 
		char ch = '\0' ;
		fscanf( pfile, "%c", &ch ) ; // 讀換行 
		int pageNum  = 0 ;
		char str[2] = "\0" ;
		int temp = -1 ; // 讀入的東西暫存
		while ( fscanf( pfile, "%c", &ch ) != EOF ) { // 一個一個讀入，並存入list(vector)中 
			if ( ch != '\n' && ch != ' ' && ch != '\t' ) {
				str[0] = ch ;
				pageNum = atoi( str ) ;
				list.push_back( pageNum ) ;
			} // if 
			
		} // while
		  
		return true ;
	} // else 
} // ReadFile()

void WriteOutput( string fileName ) { // 印答案(寫檔) 
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
    // 判斷 pageNum 是否已存在目前的 page frame中了 
	int i = 0 ;
	while ( i < cur_page_frame.size() ) {
		if ( pageNum == cur_page_frame.at(i).pageNum ) { // 已存在 
			return true ;
		} // if 
		
		i++ ;
	} // while
	
	return false ; 
} // IsInPageFrame()

void FIFO( int size, vector<int> list ) { // 先進先出頁置換法
    // size 為 page frame 的size
    int num_of_page_fault = 0 ; // 紀錄page fault次數  
    int num_of_replacement = 0 ; // 記錄置換次數 
    output_FIFO.clear() ; // 做之前，先把要輸出的答案清空 以防萬一 
    Node n ; // 東西都暫存在這裡 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // 這也是暫存的page frame樣子 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // 要跑所有的page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // 先去check是否已存在(已存在的就不用加入新的pageNum)	 
		if ( cur_page_frame.size() == size && isExist == false ) { // 目前已滿 (且要加入新的page Num)
			cur_page_frame.erase( cur_page_frame.end()-1 ) ; // 刪掉最早進入的 
			num_of_replacement++ ; // 置換一次 
		} // if
		if ( isExist == false ) { // 只要還沒存在 就可以加入新的pageNum 
			d.counter = 1 ;
			d.pageNum = n.pageNum ; 
			cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		} // if 
		
    	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // 將目前page frame的樣子都存起來 
    	
    	 
    	if ( isExist ) { // 若早已存在page frame中 
    		n.status = "" ; // 沒有page fault ，也不用更改目前page frame的樣子 
		} // if 
		else {
			n.status = "F" ; // 發生page fault 			
			num_of_page_fault++ ; // 紀錄page fault次數 
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

void AdjustPageFrame( int pageNum, vector<Data> &cur_page_frame ) { // 調整pageNum在目前page frame的位置 
	int i = 0 ;
	while ( i < cur_page_frame.size() ) { // 先找到此pageNum在哪裡，先刪掉，再插入最前面 
		if ( pageNum == cur_page_frame.at(i).pageNum ) {
			cur_page_frame.erase( cur_page_frame.begin() + i ) ;
			break ; // 結束! 跳出回全 
		} // if 
		
		i++ ;
	} // while 
} // AdjustPageFrame()


void LRU( int size, vector<int> list ) { // 最近罕用頁置換法 
	// size 為 page frame 的size
    int num_of_page_fault = 0 ; // 紀錄page fault次數  
    int num_of_replacement = 0 ; // 記錄置換次數 
    output_LRU.clear() ; // 做之前，先把要輸出的答案清空 以防萬一 
    Node n ; // 東西都暫存在這裡 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // 這也是暫存的page frame樣子 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // 要跑所有的page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // 先去check是否已存在(已存在的就不用加入新的pageNum)
			 
		if ( cur_page_frame.size() == size ) { // 目前已滿 (且要加入新的page Num)
			if ( isExist == false ) {
				num_of_replacement++ ; // 置換一次 	
				cur_page_frame.erase( cur_page_frame.end()-1 ) ; // 刪掉最早進入的 	
				n.status = "F" ; // 發生page fault 			
				num_of_page_fault++ ; // 紀錄page fault次數 
			} // if 
			else { // 已有存在 不要刪最早進入的，而是改位置即可
				n.status = "" ; // 沒有page fault ，也不用更改目前page frame的樣子 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; // 這個會刪掉pageNum這個page，底下會insert到最前面				
			} // else 
				
		} // if
		else {
			if ( isExist ) { // 若早已存在page frame中 
	    		AdjustPageFrame( n.pageNum, cur_page_frame ) ; // 這個會刪掉pageNum這個page，底下會insert到最前面
	    		n.status = "" ; // 沒有page fault ，也不用更改目前page frame的樣子 
			} // if 
			else {
				n.status = "F" ; // 發生page fault 			
				num_of_page_fault++ ; // 紀錄page fault次數 
			} // else 
		} // else 
			
		
		d.pageNum = n.pageNum ; 
		cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		
		  	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // 將目前page frame的樣子都存起來 
    	
    	 
    	
		
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
int Find_Least_Freq( vector<Data> cur_page_frame ) { // 查找page frame中 counter值最小的人，並回傳其index 
	int i = 0 ;
	int min = i ;
	while ( i < cur_page_frame.size() ) {
		// 若counter相同，則回傳最早進入的page，因為我將最新的放在page frame的最前面，
		// 所以 最早進入的page會在最後面 => 所以若counter相同，也要交換，才能達到回傳最早進入的page 
		if ( cur_page_frame.at(i).counter <= cur_page_frame.at(min).counter ) {
			min = i ;
		} // if 
		
		i++ ;
	} // while
	
	return min ; 
} // Find_Least_Freq()

int UpdateCounter( int pageNum, vector<Data> & cur_page_frame) { // 找到pageNum所在位置，並將其counter+1 
	int i = 0 ;
	while ( i < cur_page_frame.size() ) {
		if ( pageNum == cur_page_frame.at(i).pageNum ) {
			cur_page_frame.at(i).counter = cur_page_frame.at(i).counter + 1 ;
			break ; // 完成! 跳出迴圈 
		} // if 
		
		i++ ;
	} // while 
	
	return cur_page_frame.at(i).counter ;
} // UpdateCounter

void LFU( int size, vector<int> list ) { // 最不常使用頁置換法 
	// size 為 page frame 的size
    int num_of_page_fault = 0 ; // 紀錄page fault次數  
    int num_of_replacement = 0 ; // 記錄置換次數 
    output_LFU.clear() ; // 做之前，先把要輸出的答案清空 以防萬一 
    Node n ; // 東西都暫存在這裡 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // 這也是暫存的page frame樣子 
    Data d ; // 暫存的pageNum & counter 
    int i = 0 ;
    while ( i < list.size() ) { // 要跑所有的page reference
    	n.pageNum = list.at(i) ;
    	
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // 先去check是否已存在(已存在的就不用加入新的pageNum)	 
		if ( cur_page_frame.size() == size && isExist == false ) { // 目前已滿 (且要加入新的page Num)
		
			// return the index of the node which has least counter value
			int index = Find_Least_Freq( cur_page_frame ) ; 
			cur_page_frame.erase( cur_page_frame.begin() + index ) ; // 刪掉最counter最小的
			num_of_replacement++ ; // 置換一次 
		} // if
		
		if ( isExist == false ) { // 只要還沒存在 就可以加入新的pageNum  
			d.pageNum = n.pageNum ;
			d.counter = 1 ; // 第一次出現 
			cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		} // if 
		else { // 已經有存在page frame了 要更新他的counter
			d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 			
		} // else 
		
    	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // 將目前page frame的樣子都存起來 
    	
    	 
    	if ( isExist ) { // 若早已存在page frame中 
    		n.status = "" ; // 沒有page fault ，也不用更改目前page frame的樣子
		} // if 
		else {
			n.status = "F" ; // 發生page fault 			
			num_of_page_fault++ ; // 紀錄page fault次數 
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
int Find_Most_Freq( vector<Data> cur_page_frame ) { // 查找page frame中 counter值最小的人，並回傳其index 
	int i = 0 ;
	int max = i ;
	while ( i < cur_page_frame.size() ) {
		// 若counter相同，則回傳最早進入的page，因為我將最新的放在page frame的最前面，
		// 所以 最早進入的page會在最後面 => 所以若counter相同，也要交換，才能達到回傳最早進入的page 
		if ( cur_page_frame.at(i).counter >= cur_page_frame.at(max).counter ) {
			max = i ;
		} // if 
		
		i++ ;
	} // while
	
	return max ; 
} // Find_Least_Freq()


void MFU( int size, vector<int> list ) { // 最不常使用頁置換法 
	// size 為 page frame 的size
    int num_of_page_fault = 0 ; // 紀錄page fault次數  
    int num_of_replacement = 0 ; // 記錄置換次數 
    output_MFU.clear() ; // 做之前，先把要輸出的答案清空 以防萬一 
    Node n ; // 東西都暫存在這裡 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // 這也是暫存的page frame樣子 
    Data d ; // 暫存的pageNum & counter 
    int i = 0 ;
    while ( i < list.size() ) { // 要跑所有的page reference
    	n.pageNum = list.at(i) ;
    	
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // 先去check是否已存在(已存在的就不用加入新的pageNum)	 
		if ( cur_page_frame.size() == size && isExist == false ) { // 目前已滿 (且要加入新的page Num)
		
			// return the index of the node which has least counter value
			int index = Find_Most_Freq( cur_page_frame ) ; 
			cur_page_frame.erase( cur_page_frame.begin() + index ) ; // 刪掉最counter最小的
			num_of_replacement++ ; // 置換一次 
		} // if
		
		if ( isExist == false ) { // 只要還沒存在 就可以加入新的pageNum  
			d.pageNum = n.pageNum ;
			d.counter = 1 ; // 第一次出現 
			cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		} // if 
		else { // 已經有存在page frame了 要更新他的counter
			d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 			
		} // else 
		
    	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // 將目前page frame的樣子都存起來 
    	
    	 
    	if ( isExist ) { // 若早已存在page frame中 
    		n.status = "" ; // 沒有page fault ，也不用更改目前page frame的樣子
		} // if 
		else {
			n.status = "F" ; // 發生page fault 			
			num_of_page_fault++ ; // 紀錄page fault次數 
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
void LFU_LRU( int size, vector<int> list ) { // 最近罕用頁置換法 
	// size 為 page frame 的size
    int num_of_page_fault = 0 ; // 紀錄page fault次數  
    int num_of_replacement = 0 ; // 記錄置換次數 
    output_LFU_LRU.clear() ; // 做之前，先把要輸出的答案清空 以防萬一 
    Node n ; // 東西都暫存在這裡 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // 這也是暫存的page frame樣子 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // 要跑所有的page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // 先去check是否已存在(已存在的就不用加入新的pageNum)
		d.pageNum = n.pageNum ; 	 
		if ( cur_page_frame.size() == size ) { // 目前已滿 (且要加入新的page Num)
			int index = Find_Least_Freq( cur_page_frame ) ; 
			if ( isExist == false ) {
				d.counter = 1 ; // 第一次出現 
				num_of_replacement++ ; // 置換一次 	
				cur_page_frame.erase( cur_page_frame.begin() + index ) ; // 刪掉最counter最小的	
			} // if 
			else { // 不要刪最早進入的，而是改位置即可
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// 刪掉他原本的位置，最後再insert到最後面						
			} // else 							
		} // if
		else { // size還有空間 
			if ( isExist == false ) {
				d.counter = 1 ; // 第一次出現 
			} // if 
			else { // 已出現 
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// 刪掉他原本的位置，最後再insert到最後面
			} // else 
		} // else 
		
		cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
				  	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // 將目前page frame的樣子都存起來 
    	 	 
    	if ( isExist ) { // 若早已存在page frame中 
    		n.status = "" ; // 沒有page fault ，也不用更改目前page frame的樣子 
		} // if 
		else {
			n.status = "F" ; // 發生page fault 			
			num_of_page_fault++ ; // 紀錄page fault次數 
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
void MFU_LRU( int size, vector<int> list ) { // 最近罕用頁置換法 
	// size 為 page frame 的size
    int num_of_page_fault = 0 ; // 紀錄page fault次數  
    int num_of_replacement = 0 ; // 記錄置換次數 
    output_MFU_LRU.clear() ; // 做之前，先把要輸出的答案清空 以防萬一 
    Node n ; // 東西都暫存在這裡 
    bool isExist = false ;
    vector<Data> cur_page_frame ; // 這也是暫存的page frame樣子 
    Data d ;
    int i = 0 ;
    while ( i < list.size() ) { // 要跑所有的page reference
    	n.pageNum = list.at(i) ;
    	isExist = IsInPageFrame( n.pageNum, cur_page_frame ) ; // 先去check是否已存在(已存在的就不用加入新的pageNum)
		d.pageNum = n.pageNum ; 	 
		if ( cur_page_frame.size() == size ) { // 目前已滿 (且要加入新的page Num)
			int index = Find_Most_Freq( cur_page_frame ) ; 
			if ( isExist == false ) {
				d.counter = 1 ; // 第一次出現 
				num_of_replacement++ ; // 置換一次 	
				cur_page_frame.erase( cur_page_frame.begin() + index ) ; // 刪掉最counter最小的	
			} // if 
			else { // 不要刪最早進入的，而是改位置即可
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// 刪掉他原本的位置，最後再insert到最後面
						
			} // else 
							
		} // if
		else { // size還有空間 
			if ( isExist == false ) {
				d.counter = 1 ; // 第一次出現 
			} // if 
			else { // 已出現 
				d.counter = UpdateCounter( n.pageNum, cur_page_frame ) ; 
				AdjustPageFrame( n.pageNum, cur_page_frame ) ; 	// 刪掉他原本的位置，最後再insert到最後面
			} // else 
		} // else 

		
		
		cur_page_frame.insert( cur_page_frame.begin(), d ) ;			
		
		  	
    	n.pageFrame.assign( cur_page_frame.begin(), cur_page_frame.end() ) ; // 將目前page frame的樣子都存起來 
    	
    	 
    	if ( isExist ) { // 若早已存在page frame中 
    		n.status = "" ; // 沒有page fault ，也不用更改目前page frame的樣子 
		} // if 
		else {
			n.status = "F" ; // 發生page fault 			
			num_of_page_fault++ ; // 紀錄page fault次數 
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
	cout << "請輸入要讀入的檔案名稱: " ;
	cout << "\n" ;
	cin >> input_file_name ;
	bool is_method_six = false ;
	int num_of_page_frame = 0 ;
	vector<int> list ;
	
	while ( !ReadFile(input_file_name, num_of_page_frame, list ) ) {
		cout << "請輸入要讀入的檔案名稱: " ;
		cin >> input_file_name ;
	} // while 
	
	
	vector<int> list_fifo, list_lru, list_lfu, list_mfu, list_ll, list_ml ;
	// 將讀入的資料個複製一份 
	list_fifo.assign( list.begin(), list.end() ) ;
	list_lru.assign( list.begin(), list.end() ) ;
	list_lfu.assign( list.begin(), list.end() ) ;
	list_mfu.assign( list.begin(), list.end() ) ;
	list_ll.assign( list.begin(), list.end() ) ;
	list_ml.assign( list.begin(), list.end() ) ;
	// 會用到的有num_of_page_frame 跟list 
	FIFO( num_of_page_frame, list_fifo ) ; // 先進先出頁置換法
	LRU( num_of_page_frame, list_lru ) ; // 最近罕用頁置換法 
	LFU( num_of_page_frame, list_lfu ) ; // 最不常使用頁置換法 
	MFU( num_of_page_frame, list_mfu ) ; // 最常使用頁置換法 
	LFU_LRU( num_of_page_frame, list_ll ) ;
	MFU_LRU( num_of_page_frame, list_ml ) ;
	WriteOutput( input_file_name ) ;

	
	return 0;
}
