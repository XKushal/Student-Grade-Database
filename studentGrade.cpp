#include <iostream>

#include <fstream>

#include <iomanip>

#include <string>

using namespace std;



float hworkScores(istream& infile) //this function computes aggregated homewrok and class participation scor

{ 

  float hwScore, total = 0, classPart, hwprScr, minVal = 100; 

  bool error= false; 

  for (int i = 1; i<=10; i++) //reads first 10 homewrok score

    { 

      infile >> hwScore;

      if ((hwScore < 0) || (hwScore > 100)) 

                error = true;

                    

      if (hwScore < minVal) //finds minimum homewrok score

            minVal = hwScore; 

        total = total + hwScore; 

    }

        infile >> classPart;//read class participation score

          if ((classPart < 0) || (classPart > 100)) 

           error = true;

           hwprScr = (total-minVal+classPart);//gives total score

 

          hwprScr = hwprScr / 1000* 50; //total score Scaled down to total 50

   

    if (error)  

    return -1; 

  return hwprScr; 

   

} 



float tstScr(float hwprScr,istream& infile) //this function computes total aggregated test and final term scores

{ 

  float score; 

  float tstolScr = 0; 

  bool error = false; 

 

  for (int i = 1; i <= 4; i++) 

    { 

      infile >> score; 

      if ((score < 0) || (score > 100)) 

          error = true; 

    

      if (i <= 3) 

      {

        tstolScr = tstolScr + score; //gives total scores of 3 tets 

      }

      else 

      {

            tstolScr = tstolScr + (score * 2); //gives total score of 3 test terms and doubles the final term

      } 

   }

   

  tstolScr = tstolScr / 500 * 50; //total test score scaled down to total of 50

  

   if(hwprScr == -1)

   tstolScr = hwprScr;

  

  if (error) 

    return -1.0; 

  return tstolScr; 

} 



float tolScr(float hwprScr, float tstolScr) //this function adds the total aggregated score of homewrok and tests

{ 

  float finalScr; 

  bool error = false; 

 

  if (tstolScr == -1) 

    error = true; 

  finalScr = hwprScr + tstolScr; 

  if (error) 

  

    return -1; 

  return finalScr; 

} 

 

char grade(float finalScr) //this function gives the grade to the ranged scores

{ 

  char letterGrade; 

   

  if (finalScr >= 90) 

    {

        letterGrade = 'A'; 

    }

  else if (finalScr >= 80) 

   {

         letterGrade = 'B'; 

   }

  else if (finalScr >= 70) 

   {

     letterGrade = 'C'; 

   }

  else if (finalScr >= 60) 

   {

         letterGrade = 'D'; 

   }  

  else 

   {

  

    letterGrade = 'F'; 

   }

 

  if (finalScr == -1) 

    return 'Z'; 

  return letterGrade; 

} 

   

void printRecord(string name, string id, float hwprScr, float tstolScr, float finalScr,char letterGrade, ostream& outfile)

{

        outfile<<setw(20)<<name;

        outfile<<setw(10)<<id;

        outfile<<setw(8)<<hwprScr;

        outfile<<setw(8)<<tstolScr;

        outfile<<setw(8)<<finalScr;

        outfile<<setw(6)<<letterGrade;

}



int  main()

{

        ifstream infile;

        ofstream outfile;

        

        const int NAMESIZE = 20;

        char input_filename [NAMESIZE];

        

        string name, id, testscoreRecord;

        

        float hwprScr=0, tstolScr=0, finalScr=0;

        char letterGrade;

        

        cout<<"please enter the name of the input file : ";

        cin>>input_filename;

        infile.open(input_filename);



        if(!infile)// abandons operation with error mesg

        {

                cout<<"Could not open the input file\n";

                return 0;

        }

        

        outfile.open("test.txt");

        if(!outfile)

        {

                cout<<"could not open the output file\n";

                return 0;

        }

                infile>>name;//try to read a name

                

             while(!infile.eof())

                {

                        infile>>id;

                        

                        hwprScr = hworkScores(infile);//computes the final converted combined scores of homework and class participation scores

                

                        tstolScr = tstScr( hwprScr,infile);//computes the final converted scores of test and final term scores

                

                        finalScr = tolScr(hwprScr, tstolScr);//computes the sum of aggregated score of homework and test scores

                        

                        letterGrade = grade(finalScr);//computes the grade for respected obtained marks

                        

                        printRecord(name, id, hwprScr, tstolScr, finalScr, letterGrade ,outfile);

                        getline(infile,testscoreRecord); // Consume the rest of data on the line 

                        outfile<<endl;

                        infile>>name;//try to read another name

                        

                }

        

        infile.close();

        outfile.close();

        return 0;

}
