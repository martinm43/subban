
/* Testing out SO code for CPP */
/* Reading values from the sqlite api into an array*/

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <armadillo>
#include "mcss.hpp"

#define MAX_ITER 1
#define NUM_TEAMS 32

using namespace std;
using namespace arma;

//Matrix Printing Tools

template<class Matrix>
void print_matrix(Matrix matrix) {
    matrix.print(std::cout);
}

//Converting vectors from python into appropriate matrices
//and vice versa.

stdvecvec mat_to_std_vec(arma::mat &A) {
    stdvecvec V(A.n_rows);
    for (size_t i = 0; i < A.n_rows; ++i) {
        V[i] = arma::conv_to< stdvec >::from(A.row(i));
    };
    return V;
}

mat std_vec_to_HH_mat(vector< vector<double> > std_vec_array){

    vector<double> std_vec_array_flat;
    for (size_t i = 0; i < std_vec_array.size(); i++) 
        {
        vector<double> el = std_vec_array[i];
        for (size_t j=0; j < el.size(); j++) {
            std_vec_array_flat.push_back(el[j]);
        }
    }
    mat col_vec(std_vec_array_flat);
    mat mat_from_vec_t = reshape(col_vec,NUM_TEAMS,NUM_TEAMS);
    mat mat_from_vec = mat_from_vec_t.t();
    return mat_from_vec;
}

mat std_vec_to_future_mat(vector< vector<double> > std_vec_array){

    vector<double> std_vec_array_flat;
    for (size_t i = 0; i < std_vec_array.size(); i++) 
        {
        vector<double> el = std_vec_array[i];
        for (size_t j=0; j < el.size(); j++) {
            std_vec_array_flat.push_back(el[j]);
        }
    }
    mat col_vec(std_vec_array_flat);
    mat mat_from_vec_t = reshape(col_vec,3,std_vec_array.size());
    mat mat_from_vec = mat_from_vec_t.t();
    return mat_from_vec;
}

//Crude statistical model, implemented locally.

double uniformRandom() {
  return ( (double)(rand()) + 1. )/( (double)(RAND_MAX));
}

//The Monte Carlo "muscle." All SQL based functions are abstracted outside this loop
//so other more "user friendly" languages can transmit information to this loop.
mat mcss_function(mat mat_head_to_head, mat future_games, stdteamvec list_of_teams, int year, stdvec points){

    //Random info
    srand(time(NULL));

    //Two vectors for holding key information to be used later
    vector<Team> teams;

    // Matrix examples.
    mat MCSS_Head_To_Head = zeros<mat>(NUM_TEAMS,NUM_TEAMS);
    mat Sim_Total = zeros<mat>(NUM_TEAMS,NUM_TEAMS);
    mat debug_total = zeros<mat>(NUM_TEAMS,NUM_TEAMS);
    // [Division Win, Total Wins, Division Runner Up (NOT USED), Wild Card, Points] 
    mat sim_playoff_total = zeros<mat>(NUM_TEAMS,5); 
    mat error_matrix = ones<mat>(1,1);

    mat Head_To_Head = mat_head_to_head;
    //Debug Print - cout << Head_To_Head << endl;

    teams = list_of_teams;
    size_t const half_size=teams.size()/2;

    //Debug Print - cout << future_games << endl;
    int num_future_games = future_games.n_rows;

    // Debug Print - how many wins and points
    /*for(int i=0;i<NUM_TEAMS;i++){
        cout << teams[i].get_full_team_name() << ":" << teams[i].get_points() << endl;
    }*/



    for(int x_iter=0;x_iter<MAX_ITER;x_iter++){
    /* S5 - Monte Carlo Simulation */
        //set mcss head to head matrix to zero
        //and re-initialize teams.
        MCSS_Head_To_Head.zeros();
        teams = list_of_teams;

        for(int i=0;i<num_future_games;i++)
        {
            int away_team_id = future_games.row(i)[0]-1;
            int home_team_id = future_games.row(i)[1]-1;
            int awaypts = teams[away_team_id].get_points();
            int homepts = teams[home_team_id].get_points();

            if (uniformRandom()<future_games.row(i)[2]){
                MCSS_Head_To_Head.row(home_team_id)[away_team_id]++;
                teams[home_team_id].set_points(homepts+2);
                if (uniformRandom()<0.24)
                    teams[away_team_id].set_points(awaypts+1);
	    }
            else{
                MCSS_Head_To_Head.row(away_team_id)[home_team_id]++;
                teams[away_team_id].set_points(awaypts+2);
                if (uniformRandom()<0.24)
                    teams[home_team_id].set_points(homepts+1);
        }
	}

        debug_total.zeros();
        debug_total = MCSS_Head_To_Head+Head_To_Head;


	    stdvecvec htoh_records = mat_to_std_vec(debug_total);

        /*
        cout << "Head to Head" << endl;
        cout << Head_To_Head << endl;
        cout << "MCSS Head to Head" << endl;
        cout << MCSS_Head_To_Head << endl;
        */

        //Calculate raw wins - only concerned with that now (can implement tie breaking functionality later)
        //Add points as well
        mat total_wins = sum(debug_total.t());
        for(int i=0;i<NUM_TEAMS;i++){
            sim_playoff_total.row(i)[1] = sim_playoff_total.row(i)[1] +  total_wins[i];
            sim_playoff_total.row(i)[4] = sim_playoff_total.row(i)[4] +  teams[i].get_points();
            //cout << sim_playoff_total.row(i)[2] << endl;
        }
        //Create a copy of the teams list, only defined in the scope of this loop
        vector<Team> sim_teams = teams;
	
        //Round all wins
        for(int i=0;i<NUM_TEAMS;i++){
            sim_teams[i].set_total_wins(round(total_wins[i]));
            sim_teams[i].set_htoh(htoh_records[i]);
	    }
        //random_shuffle is deprecated in C++17 but this code will not be c++17 compliant.
        random_shuffle(sim_teams.begin(),sim_teams.end());
	    sort(sim_teams.begin(),sim_teams.end(),teams_sort());

        //Create conference based vectors. 
        vector<Team>::const_iterator first = sim_teams.begin();
        vector<Team>::const_iterator mid = sim_teams.begin() + half_size;
        vector<Team>::const_iterator last = sim_teams.end();
        vector<Team> east_conf(first,mid);
        vector<Team> west_conf(mid+1,last); //When you split, you need to start one more entry over.

       //MODERN: Format for 2013-2014 through 2022-23 excluding the COVID (2019-20) and CANDIV (2020-21) seasons
       if(((year >= 2014)&&(year<=2019)) || (year >= 2022))
       {
       //iterate through list of teams to determine playoff teams.
           
	    sort(sim_teams.begin(),sim_teams.end(),teams_sort());
            for(int i=0;i<NUM_TEAMS;i++){
            string team_name = sim_teams[i].get_full_team_name();
            string team_division = sim_teams[i].get_division();
            int print_points = sim_teams[i].get_points();
            int print_total_wins = sim_teams[i].get_total_wins();
            int team_id = sim_teams[i].get_team_id();
            cout << i << ":" << team_name << ":" << team_division << ":" 
                << print_points << ":wins:" << print_total_wins << endl;
            if(( i >= 0 && i <= 2) || (i >= 8 && i <= 10)||(i >= 16 && i <= 18)||(i >= 24 && i <= 26)){
                sim_playoff_total.row(team_id-1)[0]++; //Division Winner
            }
        }

        //East Conference Wild Cards.
        vector<Team> east_wild_card;
        east_wild_card.push_back(sim_teams[3]); //Division Group Atlantic remaining top two
        east_wild_card.push_back(sim_teams[4]); 	
        east_wild_card.push_back(sim_teams[19]); //Division Group Metro remaining top two	
        east_wild_card.push_back(sim_teams[20]); 	
        sort(east_wild_card.begin(),east_wild_card.end(),points_sort());        
        int east_wc1 = east_wild_card[0].get_team_id();
        int east_wc2 = east_wild_card[1].get_team_id();
        sim_playoff_total.row(east_wc1-1)[3]++; //WC Winner 
        sim_playoff_total.row(east_wc2-1)[3]++;  //WC winner
        
        //West Wild Cards
        vector<Team> west_wild_card;
        west_wild_card.push_back(sim_teams[11]); //Division Group Central remaining top two	
        west_wild_card.push_back(sim_teams[12]); 	
        west_wild_card.push_back(sim_teams[27]); //Division Group Pacific remaining top two	
        west_wild_card.push_back(sim_teams[28]); 
        sort(west_wild_card.begin(),west_wild_card.end(),points_sort());        
        int west_wc1 = west_wild_card[0].get_team_id();
        int west_wc2 = west_wild_card[1].get_team_id();
        sim_playoff_total.row(west_wc1-1)[3]++; //WC Winner
        sim_playoff_total.row(west_wc2-1)[3]++;  //WC Winner
        }

        //Format for 2001-2013 inclusive
        
        if((year >= 2001)&&(year<=2013)){
       //iterate through list of teams to determine division winners.
       for(int i=0;i<NUM_TEAMS;i++){
            string team_name = sim_teams[i].get_full_team_name();
            string team_division = sim_teams[i].get_division();
            int print_points = sim_teams[i].get_points();
            int team_id = sim_teams[i].get_team_id();
	        sort(sim_teams.begin(),sim_teams.end(),teams_sort());        
            cout << i << ":" << team_name << ":" << team_division << ":" << print_points << endl;
            if((i == 2) || (i==7)||(i==12)||(i==17)||(i==22)||(i==27)){
                sim_playoff_total.row(team_id-1)[0]++; //Division Winner
            }
        }

        //East Wild Cards
	

        vector<Team> east_wild_card;
        //Select all non div win teams in east conf
        east_wild_card.push_back(sim_teams[3]);
        east_wild_card.push_back(sim_teams[4]); 
        east_wild_card.push_back(sim_teams[5]); 
        east_wild_card.push_back(sim_teams[6]); 
        east_wild_card.push_back(sim_teams[13]); 
        east_wild_card.push_back(sim_teams[14]); 
        east_wild_card.push_back(sim_teams[15]); 
        east_wild_card.push_back(sim_teams[16]); 
        east_wild_card.push_back(sim_teams[28]); 
        east_wild_card.push_back(sim_teams[29]); 
        east_wild_card.push_back(sim_teams[30]); 
        east_wild_card.push_back(sim_teams[31]); 
        sort(east_wild_card.begin(),east_wild_card.end(),points_sort());  
        cout<<"East Teams"<<endl;
        for (Team i : east_wild_card){
            cout << i.get_full_team_name() << ":" << i.get_division() << ":" << i.get_points() << endl;
        }    
        int east_wc1 = east_wild_card[0].get_team_id();
        int east_wc2 = east_wild_card[1].get_team_id();
        int east_wc3 = east_wild_card[2].get_team_id();
        int east_wc4 = east_wild_card[3].get_team_id();
        int east_wc5 = east_wild_card[4].get_team_id();
        sim_playoff_total.row(east_wc1-1)[3]++; 
        sim_playoff_total.row(east_wc2-1)[3]++; 
        sim_playoff_total.row(east_wc3-1)[3]++; 
        sim_playoff_total.row(east_wc4-1)[3]++; 
        sim_playoff_total.row(east_wc5-1)[3]++; 
        
        //West Wild Cards
        vector<Team> west_wild_card;
        west_wild_card.push_back(sim_teams[8]);
        west_wild_card.push_back(sim_teams[9]); 
        west_wild_card.push_back(sim_teams[10]); 
        west_wild_card.push_back(sim_teams[11]); 
        west_wild_card.push_back(sim_teams[18]); 
        west_wild_card.push_back(sim_teams[19]); 
        west_wild_card.push_back(sim_teams[20]); 
        west_wild_card.push_back(sim_teams[21]); 
        west_wild_card.push_back(sim_teams[23]); 
        west_wild_card.push_back(sim_teams[24]); 
        west_wild_card.push_back(sim_teams[25]); 
        west_wild_card.push_back(sim_teams[26]); 
        sort(west_wild_card.begin(),west_wild_card.end(),points_sort());
        cout<<"West Teams"<<endl;
        for (Team i : west_wild_card){
            cout << i.get_full_team_name() << ":" << i.get_division() << ":" << i.get_points() << endl;
        }
        int west_wc1 = west_wild_card[0].get_team_id();
        int west_wc2 = west_wild_card[1].get_team_id();
        int west_wc3 = west_wild_card[2].get_team_id();
        int west_wc4 = west_wild_card[3].get_team_id();
        int west_wc5 = west_wild_card[4].get_team_id();
        sim_playoff_total.row(west_wc1-1)[3]++; 
        sim_playoff_total.row(west_wc2-1)[3]++; 
        sim_playoff_total.row(west_wc3-1)[3]++; 
        sim_playoff_total.row(west_wc4-1)[3]++; 
        sim_playoff_total.row(west_wc5-1)[3]++; 
        }
	
    for(int i=0;i<NUM_TEAMS;i++){
        sim_playoff_total.row(i)[0] = sim_playoff_total.row(i)[0]/MAX_ITER;
        sim_playoff_total.row(i)[1] = sim_playoff_total.row(i)[1]/MAX_ITER;
        sim_playoff_total.row(i)[2] = sim_playoff_total.row(i)[2]/MAX_ITER;
        sim_playoff_total.row(i)[3] = sim_playoff_total.row(i)[3]/MAX_ITER;
        sim_playoff_total.row(i)[4] = sim_playoff_total.row(i)[4]/MAX_ITER;
    }

    //cout << MAX_ITER << " simulations complete." << endl; //--not necessary.
    return sim_playoff_total;
    }
}

//only require this instantiation as we are only using the vanilla analysis tool
template void print_matrix<arma::mat>(arma::mat matrix);

stdvecvec simulations_result_vectorized(stdvecvec head_to_head_list_python, stdvecvec future_games_list_python, stdteamvec teams_list_python, int year, stdvec points_list_python){
    mat head_to_head_mat = std_vec_to_HH_mat(head_to_head_list_python);
    mat future_mat = std_vec_to_future_mat(future_games_list_python);
    stdteamvec teams = teams_list_python; 
    stdvec points = points_list_python;
    //cout << future_mat << endl;
    mat sim_results = mcss_function(head_to_head_mat,future_mat,teams,year,points);
    return mat_to_std_vec(sim_results);
}


//C++ Printing and processing function.
int main()
{

return 0;
}
