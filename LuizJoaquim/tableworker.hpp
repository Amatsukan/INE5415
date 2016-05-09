     /**///*****************************************************///
    /**///-----------------------//----------------------------///
       #include <string>        // std::string                 //
      #include <fstream>       // std::multimap               //
  /**///______________________//____________________________///
 /**///****************************************************///

class TableWorker{
    ofstream inputFile, outputFile;

    void OpenOutputFile(){
        outputFile.open ("teste1AfndAfd.out");
    }

    void OpenInputFile(){
        inputFile.open ("teste1AfndAfd.in");
    }

    void CloseFiles(){
        inputFile.close();
        outputFile.close();
    }


};
