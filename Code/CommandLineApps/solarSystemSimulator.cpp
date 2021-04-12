#include "CLI11.hpp"
#include "nbsimMassiveParticle.h"
#include "nbsimSolarSystemData.ipp"
#include <iostream>
#include <chrono>
#include <omp.h>

// help function to add appropriate messages to screen summarising the position of the solar system bodies
void Print2Screen(std::vector<std::shared_ptr<nbsim::MassiveParticle>> ListofPlanets){

    for(int i = 0; i < 9; i++){

        std::string name = nbsim::solarSystemData[i].name;
        std::cout <<"The position of " + name + " is: (" << ListofPlanets[i]->getPosition()[0] << ", " 
        << ListofPlanets[i]->getPosition()[1] << ", " << ListofPlanets[i]->getPosition()[2] << ")" << std::endl;
    }

    std::cout<<" "<<std::endl;

}


// function to output centre of mass vector of the system to screen as the simulation evolves
double CenterofMass(std::vector<std::shared_ptr<nbsim::MassiveParticle>> ListofPlanets){

    Eigen::Vector3d r_com;
    Eigen::Vector3d nominator(0.0,0.0,0.0);
    double denominator = 0.0;

    for(int i = 0; i < 9; i++){

        nominator = nominator + (ListofPlanets[i]->getMu()) * (ListofPlanets[i]->getPosition());
        denominator = denominator + ListofPlanets[i]->getMu();
    }

    r_com = nominator/denominator;

    std::cout<<"The centre of mass vector of the system is: ("<<r_com[0]<<","<<r_com[1]<<","<<r_com[2]<<")"<<std::endl;

    return sqrt(r_com.dot(r_com));

}


// function to output total linear momentum vector the system to screen as the simulation evolves
double LinearMomentum(std::vector<std::shared_ptr<nbsim::MassiveParticle>> ListofPlanets){

    Eigen::Vector3d p_total;

    for(int i = 0; i < 9; i++){

        p_total = p_total + (ListofPlanets[i]->getMu())*(ListofPlanets[i]->getVelocity());

    }

    std::cout<<"The total linear momentum vector of the system is: ("<<p_total[0]<<","<<p_total[1]<<","<<p_total[2]<<")"<<std::endl;
    
    return sqrt(p_total.dot(p_total));

}


// command line app
int main(int argc, char **argv) {
    
	CLI::App app{"Model the motion of Sun and planets in the Solar System"};

    double step_size;
    
    CLI::Option* opt1 = app.add_option("-s,--stepsize",step_size, "argument to control the step_size"); 


    int num_stepsize;

    CLI::Option* opt2 = app.add_option("-n,--number", num_stepsize, "argunment to control the number of timesteps");
    
    CLI11_PARSE(app, argc, argv);

    if(*opt1 and *opt2){

        // vector which store sun and eight planets
        std::vector<std::shared_ptr<nbsim::MassiveParticle>> ListofPlanets;
        
        // initialise nine planets
        for(int i = 0; i < 9; i++){

            std::shared_ptr<nbsim::MassiveParticle> M_Plant(new nbsim::MassiveParticle(nbsim::solarSystemData[i].position,nbsim::solarSystemData[i].velocity, nbsim::solarSystemData[i].mu));

            ListofPlanets.push_back(M_Plant);
        }

        // add all other bodies to every body
        for(int i = 0; i < 9; i++){

            for (int j = 0; j < 9; j++){

                if (i != j){

                    ListofPlanets[i]->addAttractor(ListofPlanets[j]);
                }
            }
        }

        //Output messages to summarise the position of the solar system at the start of simulation
        std::cout << "At the start of the solar system simulation: " << std::endl;
        double r_com = CenterofMass(ListofPlanets);
        double p_total = LinearMomentum(ListofPlanets);
        std::cout<<"Both vectors are closed to null, and the position of sun and eight planets are listed below:"<<std::endl;
        Print2Screen(ListofPlanets);


        // benchmark the time for one year simulation
        std::clock_t c_start = std::clock();
        auto t_start = std::chrono::high_resolution_clock::now();
        

        // implement the evolution of the solar system
        for(int num = 0; num < num_stepsize; num++){

            // update gravitational acceleration for all bodies
            omp_set_num_threads (18);
            #pragma omp parallel for 
            for(int i = 0; i < 9; i++){
                
                ListofPlanets[i] -> calculateAcceleration();
                
            }

            // update the position and velocity of each body
            #pragma omp parallel for 
            for(int j = 0; j < 9; j++){
                
                ListofPlanets[j] -> integrateTimestep(step_size);

            }
            
            
            #ifdef DEBUG
                std::cout<<"In the "<<num+1<<" timesteps"<<std::endl; 
                r_com = CenterofMass(ListofPlanets);
                p_total = LinearMomentum(ListofPlanets);
                std::cout<<"--------------------------------------------------------------------------"<<std::endl;
            #endif

        }


        // benchmark time
        std::clock_t c_end = std::clock();
        auto t_end = std::chrono::high_resolution_clock::now();
        
        //Output messages to summarise the position of the solar system at the end of simulation
        std::cout << "At the end of the solar system simulation: " << std::endl;
        r_com = CenterofMass(ListofPlanets);
        p_total = LinearMomentum(ListofPlanets);
        std::cout<<"The values of |r_com| and |p_total| are: "<<r_com<<" and "<<p_total<<", which are both within 0.0001AU of the origin."<<std::endl;
        std::cout<<"The position of sun and eight planets are listed below:"<<std::endl;
        Print2Screen(ListofPlanets);

        // output messages about time consuming for the simulation
        std::cout <<"CPU time used: "
                  << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
                  << "Wall clock time passed: "
                  << std::chrono::duration<double, std::milli>(t_end-t_start).count()<< " ms\n";


    // if none options is specified by users
    }else if(! *opt1 and ! *opt2){
        std::cout<<"Model the motion of Sun and planets in the Solar System"<<std::endl;

        std::cout<<"Usage: ./bin/solarSystemSimulator [OPTIONS]"<<std::endl;
            
        std::cout<<"Please specify [Options] for simulating solar system. Use '-h' or --'help' to gain more help information"<<std::endl;
        
    // if option of filename if not specified by users
    }else if (! *opt1){

        std::cout<<"Please use option '-s' or '--stepsize' to specify the value of step_size" <<std::endl;
        
    // if option of methods if not specified by users
    }else if(! *opt2){

        std::cout<<"Please use option '-n' or '--number' to specify the total number of timesteps" <<std::endl;

    }
    
    return 0;
    
    
}