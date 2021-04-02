#include "CLI11.hpp"
#include "nbsimMassiveParticle.h"
#include "nbsimSolarSystemData.ipp"
#include <iostream>


void Print2Screen(std::vector<std::shared_ptr<nbsim::MassiveParticle>> ListofPlanets){

    for(int i = 0; i < 9; i++){

        std::string name = nbsim::solarSystemData[i].name;
        std::cout <<"The position of " + name + " is: (" << ListofPlanets[i]->getPosition()[0] << ", " 
        << ListofPlanets[i]->getPosition()[1] << ", " << ListofPlanets[i]->getPosition()[2] << ")" << std::endl;
    }

    std::cout<<" "<<std::endl;

}


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




int main(int argc, char **argv) {
    
	CLI::App app{"Model the motion of Sun and planets in the Solar System"};

    double step_size;
    
    CLI::Option* opt1 = app.add_option("-s,--stepsize",step_size, "argument to control the step_size"); 


    int num_stepsize;

    CLI::Option* opt2 = app.add_option("-n,--number", num_stepsize, "argunment to control the number of timesteps");
    
    CLI11_PARSE(app, argc, argv);

    if(*opt1 and *opt2){

        std::cout << step_size << std::endl;
        std::cout << num_stepsize << std::endl;

        // vector which store sun and eight planets
        std::vector<std::shared_ptr<nbsim::MassiveParticle>> ListofPlanets;
        
        // initialise nine plants
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

        
        std::cout << "the position of the solar system bodies at the start of the simulation: " << std::endl;
        Print2Screen(ListofPlanets);

        // implement the evolution of the solar system
        for(int num = 0; num < num_stepsize; num++){

            // update gravitational aceleration for all bodies
            for(int i = 0; i < 9; i++){

                ListofPlanets[i] -> calculateAcceleration();

            }

            // update the position and velocity of each body
            for(int j = 0; j < 9; j++){

                ListofPlanets[j] -> integrateTimestep(step_size);

            }

        }

        std::cout << "the position of the solar system bodies at the end of the simulation: " << std::endl;
        Print2Screen(ListofPlanets);

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