/*
 * Test_field_io.cpp, part of Hadrons (https://github.com/aportelli/Hadrons)
 *
 * Copyright (C) 2015 - 2023
 *
 * Author: Antonin Portelli <antonin.portelli@me.com>
 *
 * Hadrons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hadrons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hadrons.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See the full license in the file "LICENSE" in the top level distribution 
 * directory.
 */

/*  END LEGAL */
#include <Hadrons/Environment.hpp>
#include <Hadrons/Modules.hpp>
#include <Hadrons/Application.hpp>
#include <Hadrons/Global.hpp>

using namespace Grid;
using namespace Hadrons;

int main(int argc, char *argv[])
{
    // initialization //////////////////////////////////////////////////////////
    Grid_init(&argc, &argv);
    HadronsLogError.Active(GridLogError.isActive());
    HadronsLogWarning.Active(GridLogWarning.isActive());
    HadronsLogMessage.Active(GridLogMessage.isActive());
    HadronsLogIterative.Active(GridLogIterative.isActive());
    HadronsLogDebug.Active(GridLogDebug.isActive());
    LOG(Message) << "Grid initialized" << std::endl;

    Application            application;
    Application::GlobalPar globalPar; 
    MIO::SaveIldgPar       ildgPar;

    globalPar.runId = "Test_ildg_io";
    globalPar.trajCounter.start = 1;
    globalPar.trajCounter.end = 3;
    globalPar.trajCounter.step = 1;

    application.setPar(globalPar);
    application.createModule<MGauge::Unit>("lattice");

    ildgPar.gauge = "lattice";          // name of gauge field
    ildgPar.fileStem = "ildg_test";     // stem of filename
    ildgPar.ensembleLabel = "su3gauge"; // add suffix gauge_fixed_su3
    ildgPar.ensembleId = "telos";       // collaboration label
  
    ildgPar.gaugeGroup = "SU";

    application.createModule<MIO::SaveIldg>("save-ildg-lattice", ildgPar);

    application.run();

    Grid_finalize();
    
    return EXIT_SUCCESS;
}
