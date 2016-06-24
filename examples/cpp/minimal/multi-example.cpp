/**********************************************************************************

 Infomap software package for multi-level network clustering

 Copyright (c) 2013, 2014 Daniel Edler, Martin Rosvall

 For more information, see <http://www.mapequation.org>


 This file is part of Infomap software package.

 Infomap software package is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Infomap software package is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with Infomap software package.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <Infomap.h>
#include <Infomap/MultiplexNetwork.h>

using std::vector;
using std::string;

void parseM2ClusterInfo(std::string line, int &n1, int &n2){
	std::istringstream m_extractor;
	m_extractor.clear();
    m_extractor.str(line);
    std::string tmpString;
    if (!(m_extractor >> n1 >> tmpString >> n2)) {
        std::cout << "error" << std::endl;
    }
}

void printClusters(infomap::HierarchicalNetwork & tree) {
	int n1, n2;
    std::cout << "\nClusters:\n#layer node clusterIndex:\n";
    for (infomap::LeafIterator leafIt(&tree.getRootNode()); !leafIt.isEnd(); ++leafIt) {
    	parseM2ClusterInfo(leafIt->data.name, n1, n2);
        std::cout << n1 << " " << n2 << " " << leafIt.clusterIndex() << '\n';
    }
}

int main(int argc, char** argv)
{
	infomap::Config config = infomap::init("--two-level -imultiplex -N2 --expanded");

	infomap::MultiplexNetwork network(config);

	network.addMultiplexLink(2, 1, 1, 2, 1.0);
	network.addMultiplexLink(1, 2, 2, 1, 1.0);
	network.addMultiplexLink(3, 2, 2, 3, 1.0);

	infomap::HierarchicalNetwork resultNetwork(config);

	int exitCode = infomap::run(network, resultNetwork);

	if (exitCode == 0)
		printClusters(resultNetwork);
}
