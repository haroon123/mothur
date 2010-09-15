/*
 *  commandfactory.cpp
 *  
 *
 *  Created by Pat Schloss on 10/25/08.
 *  Copyright 2008 Patrick D. Schloss. All rights reserved.
 *
 */

#include "command.hpp"
#include "readdistcommand.h"
#include "readtreecommand.h"
#include "readotucommand.h"
#include "clustercommand.h"
#include "collectcommand.h"
#include "collectsharedcommand.h"
#include "getgroupcommand.h"
#include "getlabelcommand.h"
#include "rarefactcommand.h"
#include "summarycommand.h"
#include "summarysharedcommand.h"
#include "rarefactsharedcommand.h"
#include "quitcommand.h"
#include "helpcommand.h"
#include "commandfactory.hpp"
#include "deconvolutecommand.h"
#include "parsimonycommand.h"
#include "unifracunweightedcommand.h"
#include "unifracweightedcommand.h"
#include "libshuffcommand.h"
#include "heatmapcommand.h"
#include "heatmapsimcommand.h"
#include "filterseqscommand.h"
#include "venncommand.h"
#include "nocommands.h"
#include "binsequencecommand.h"
#include "getoturepcommand.h"
#include "treegroupscommand.h"
#include "bootstrapsharedcommand.h"
//#include "consensuscommand.h"
#include "distancecommand.h"
#include "aligncommand.h"
#include "matrixoutputcommand.h"
#include "getsabundcommand.h"
#include "getrabundcommand.h"
#include "seqsummarycommand.h"
#include "screenseqscommand.h"
#include "reversecommand.h"
#include "trimseqscommand.h"
#include "mergefilecommand.h"
#include "chimeraseqscommand.h"
#include "listseqscommand.h"
#include "getseqscommand.h"
#include "removeseqscommand.h"
#include "systemcommand.h"
#include "secondarystructurecommand.h"
#include "getsharedotucommand.h"
#include "getlistcountcommand.h"
#include "hclustercommand.h"
#include "classifyseqscommand.h"
#include "phylotypecommand.h"
#include "mgclustercommand.h"
#include "preclustercommand.h"
#include "pcacommand.h"
#include "otuhierarchycommand.h"
#include "setdircommand.h"
#include "parselistscommand.h"
#include "parsesffcommand.h"
#include "chimeraccodecommand.h"
#include "chimeracheckcommand.h"
#include "chimeraslayercommand.h"
#include "chimerapintailcommand.h"
#include "chimerabellerophoncommand.h"
#include "setlogfilecommand.h"
#include "phylodiversitycommand.h"
#include "makegroupcommand.h"
#include "chopseqscommand.h"
#include "clearcutcommand.h"
#include "catchallcommand.h"
#include "splitabundcommand.h"
#include "clustersplitcommand.h"
#include "classifyotucommand.h"
#include "degapseqscommand.h"
#include "getrelabundcommand.h"
#include "sensspeccommand.h"
#include "sffinfocommand.h"
#include "seqerrorcommand.h"
#include "normalizesharedcommand.h"

/*******************************************************/

/******************************************************/
CommandFactory* CommandFactory::getInstance() {
	if( _uniqueInstance == 0) {
		_uniqueInstance = new CommandFactory();
	}
	return _uniqueInstance;
}
/***********************************************************/

/***********************************************************/
//note: This class is resposible for knowing which commands are mpiEnabled,
//If a command is not enabled only process 0 will execute the command. 
//This avoids redundant outputs on pieces of code we have not paralellized. 
//If you add mpi code to a existing command you need to modify the list below or the code will hang on MPI blocking commands like FIle_open. 
//example:  commands["dist.seqs"] = "MPIEnabled";

CommandFactory::CommandFactory(){
	string s = "";
	m = MothurOut::getInstance();
	
	command = new NoCommand(s);
	
	outputDir = ""; inputDir = "";
	logFileName = "";
	append = false;
	
	//initialize list of valid commands
	commands["read.dist"]			= "read.dist"; 
	commands["read.otu"]			= "read.otu";
	commands["read.tree"]			= "read.tree"; 
	commands["bin.seqs"]			= "bin.seqs"; 
	commands["get.oturep"]			= "get.oturep";
	commands["cluster"]				= "cluster"; 
	commands["unique.seqs"]			= "unique.seqs"; 
	commands["dist.shared"]			= "dist.shared";
	commands["collect.single"]		= "collect.single"; 
	commands["collect.shared"]		= "collect.shared"; 
	commands["rarefaction.single"]	= "rarefaction.single"; 
	commands["rarefaction.shared"]	= "rarefaction.shared"; 
	commands["summary.single"]		= "summary.single"; 
	commands["summary.shared"]		= "summary.shared"; 
	commands["parsimony"]			= "parsimony";
	commands["unifrac.weighted"]	= "unifrac.weighted"; 
	commands["unifrac.unweighted"]	= "unifrac.unweighted"; 
	commands["libshuff"]			= "libshuff";
	commands["tree.shared"]			= "tree.shared";
	commands["heatmap.bin"]			= "heatmap.bin";
	commands["heatmap.sim"]			= "heatmap.sim";
	commands["venn"]				= "venn";
	commands["get.group"]           = "get.group";
	commands["get.label"]           = "get.label";
	commands["get.sabund"]          = "get.sabund";
	commands["get.rabund"]          = "get.rabund";
	commands["bootstrap.shared"]	= "bootstrap.shared";
	//commands["consensus"]			= "consensus";
	commands["help"]				= "help";
	commands["reverse.seqs"]		= "reverse.seqs";
	commands["trim.seqs"]			= "trim.seqs";
	commands["list.seqs"]			= "list.seqs";
	commands["get.seqs"]			= "get.seqs";
	commands["remove.seqs"]			= "get.seqs";
	commands["system"]				= "system";
	commands["align.check"]			= "align.check";
	commands["get.sharedseqs"]		= "get.sharedseqs";
	commands["get.otulist"]			= "get.otulist";
	commands["hcluster"]			= "hcluster"; 
	commands["phylotype"]			= "phylotype";
	commands["mgcluster"]			= "mgcluster";
	commands["pre.cluster"]			= "pre.cluster";
	commands["pcoa"]				= "pcoa";
	commands["otu.hierarchy"]		= "otu.hierarchy";
	commands["set.dir"]				= "set.dir";
	commands["merge.files"]			= "merge.files";
	commands["parse.list"]			= "parse.list";
	commands["parse.sff"]			= "parse.sff";
	commands["set.logfile"]			= "set.logfile";
	commands["phylo.diversity"]		= "phylo.diversity";
	commands["make.group"]			= "make.group";
	commands["chop.seqs"]			= "chop.seqs";
	commands["clearcut"]			= "clearcut";
	commands["catchall"]			= "catchall";
	commands["split.abund"]			= "split.abund";
	commands["classify.otu"]		= "classify.otu";
	commands["degap.seqs"]			= "degap.seqs";
	commands["get.relabund"]		= "get.relabund";
	commands["sffinfo"]				= "sffinfo";
	commands["normalize.shared"]	= "normalize.shared";
	commands["classify.seqs"]		= "MPIEnabled"; 
	commands["dist.seqs"]			= "MPIEnabled";
	commands["filter.seqs"]			= "MPIEnabled";
	commands["align.seqs"]			= "MPIEnabled";
	commands["chimera.seqs"]		= "chimera.seqs";
	commands["chimera.ccode"]		= "MPIEnabled";
	commands["chimera.check"]		= "MPIEnabled";
	commands["chimera.slayer"]		= "MPIEnabled";
	commands["chimera.pintail"]		= "MPIEnabled";
	commands["chimera.bellerophon"]	= "MPIEnabled";
	commands["screen.seqs"]			= "MPIEnabled";
	commands["summary.seqs"]		= "MPIEnabled";
	commands["cluster.split"]		= "MPIEnabled";
	commands["sens.spec"]			= "sens.spec";
	commands["seq.error"]			= "seq.error";
	commands["quit"]				= "MPIEnabled"; 

}
/***********************************************************/

/***********************************************************/
bool CommandFactory::MPIEnabled(string commandName) {
	bool mpi = false;
	it = commands.find(commandName);
	if (it != commands.end()) { 
		if (it->second == "MPIEnabled") { return true; }
	}
	return mpi;
}
/***********************************************************/

/***********************************************************/
CommandFactory::~CommandFactory(){
	_uniqueInstance = 0;
	delete command;
}

/***********************************************************/

/***********************************************************/
//This function calls the appropriate command fucntions based on user input.
Command* CommandFactory::getCommand(string commandName, string optionString){
	try {
		delete command;   //delete the old command
		
		//user has opted to redirect output from dir where input files are located to some other place
		if (outputDir != "") { 
			if (optionString != "") { optionString += ", outputdir=" + outputDir; }
			else { optionString += "outputdir=" + outputDir; }
		}
		
		//user has opted to redirect input from dir where mothur.exe is located to some other place
		if (inputDir != "") { 
			if (optionString != "") { optionString += ", inputdir=" + inputDir; }
			else { optionString += "inputdir=" + inputDir; }
		}
		
		if(commandName == "read.dist")					{	command = new ReadDistCommand(optionString);				}
		else if(commandName == "read.otu")				{	command = new ReadOtuCommand(optionString);					}
		else if(commandName == "read.tree")				{	command = new ReadTreeCommand(optionString);				}
		else if(commandName == "cluster")				{	command = new ClusterCommand(optionString);					}
		else if(commandName == "unique.seqs")			{	command = new DeconvoluteCommand(optionString);				}
		else if(commandName == "parsimony")				{	command = new ParsimonyCommand(optionString);				}
		else if(commandName == "help")					{	command = new HelpCommand(optionString);					}
		else if(commandName == "quit")					{	command = new QuitCommand(optionString);					}
		else if(commandName == "collect.single")		{	command = new CollectCommand(optionString);					}
		else if(commandName == "collect.shared")		{	command = new CollectSharedCommand(optionString);			}
		else if(commandName == "rarefaction.single")	{	command = new RareFactCommand(optionString);				}
		else if(commandName == "rarefaction.shared")	{	command = new RareFactSharedCommand(optionString);			}
		else if(commandName == "summary.single")		{	command = new SummaryCommand(optionString);					}
		else if(commandName == "summary.shared")		{	command = new SummarySharedCommand(optionString);			}
		else if(commandName == "unifrac.weighted")		{	command = new UnifracWeightedCommand(optionString);			}
		else if(commandName == "unifrac.unweighted")	{	command = new UnifracUnweightedCommand(optionString);		}
		else if(commandName == "get.group")             {   command = new GetgroupCommand(optionString);				}
		else if(commandName == "get.label")             {   command = new GetlabelCommand(optionString);				}
		else if(commandName == "get.sabund")            {   command = new GetSAbundCommand(optionString);				}
		else if(commandName == "get.rabund")            {   command = new GetRAbundCommand(optionString);				}
		else if(commandName == "libshuff")              {   command = new LibShuffCommand(optionString);				}
		else if(commandName == "heatmap.bin")			{   command = new HeatMapCommand(optionString);					}
		else if(commandName == "heatmap.sim")			{   command = new HeatMapSimCommand(optionString);				}
		else if(commandName == "filter.seqs")			{   command = new FilterSeqsCommand(optionString);				}
		else if(commandName == "venn")					{   command = new VennCommand(optionString);					}
		else if(commandName == "bin.seqs")				{   command = new BinSeqCommand(optionString);					}
		else if(commandName == "get.oturep")			{   command = new GetOTURepCommand(optionString);				}
		else if(commandName == "tree.shared")			{   command = new TreeGroupCommand(optionString);				}
		else if(commandName == "dist.shared")			{   command = new MatrixOutputCommand(optionString);			}
		else if(commandName == "bootstrap.shared")		{   command = new BootSharedCommand(optionString);				}
		else if(commandName == "consensus")				{   command = new ConcensusCommand(optionString);				}
		else if(commandName == "dist.seqs")				{   command = new DistanceCommand(optionString);				}
		else if(commandName == "align.seqs")			{   command = new AlignCommand(optionString);					}
		else if(commandName == "summary.seqs")			{	command = new SeqSummaryCommand(optionString);				}
		else if(commandName == "screen.seqs")			{	command = new ScreenSeqsCommand(optionString);				}
		else if(commandName == "reverse.seqs")			{	command = new ReverseSeqsCommand(optionString);				}
		else if(commandName == "trim.seqs")				{	command = new TrimSeqsCommand(optionString);				}
		else if(commandName == "chimera.seqs")			{	command = new ChimeraSeqsCommand(optionString);				}
		else if(commandName == "list.seqs")				{	command = new ListSeqsCommand(optionString);				}
		else if(commandName == "get.seqs")				{	command = new GetSeqsCommand(optionString);					}
		else if(commandName == "remove.seqs")			{	command = new RemoveSeqsCommand(optionString);				}
		else if(commandName == "merge.files")			{	command = new MergeFileCommand(optionString);				}
		else if(commandName == "system")				{	command = new SystemCommand(optionString);					}
		else if(commandName == "align.check")			{	command = new AlignCheckCommand(optionString);				}
		else if(commandName == "get.sharedseqs")		{	command = new GetSharedOTUCommand(optionString);			}
		else if(commandName == "get.otulist")			{	command = new GetListCountCommand(optionString);			}
		else if(commandName == "hcluster")				{	command = new HClusterCommand(optionString);				}
		else if(commandName == "classify.seqs")			{	command = new ClassifySeqsCommand(optionString);			}
		else if(commandName == "chimera.ccode")			{	command = new ChimeraCcodeCommand(optionString);			}
		else if(commandName == "chimera.check")			{	command = new ChimeraCheckCommand(optionString);			}
		else if(commandName == "chimera.slayer")		{	command = new ChimeraSlayerCommand(optionString);			}
		else if(commandName == "chimera.pintail")		{	command = new ChimeraPintailCommand(optionString);			}
		else if(commandName == "chimera.bellerophon")	{	command = new ChimeraBellerophonCommand(optionString);		}
		else if(commandName == "phylotype")				{	command = new PhylotypeCommand(optionString);				}
		else if(commandName == "mgcluster")				{	command = new MGClusterCommand(optionString);				}
		else if(commandName == "pre.cluster")			{	command = new PreClusterCommand(optionString);				}
		else if(commandName == "pcoa")					{	command = new PCACommand(optionString);						}
		else if(commandName == "otu.hierarchy")			{	command = new OtuHierarchyCommand(optionString);			}
		else if(commandName == "set.dir")				{	command = new SetDirectoryCommand(optionString);			}
		else if(commandName == "set.logfile")			{	command = new SetLogFileCommand(optionString);				}
		else if(commandName == "parse.list")			{	command = new ParseListCommand(optionString);				}
		else if(commandName == "parse.sff")				{	command = new ParseSFFCommand(optionString);				}
		else if(commandName == "phylo.diversity")		{	command = new PhyloDiversityCommand(optionString);			}
		else if(commandName == "make.group")			{	command = new MakeGroupCommand(optionString);				}
		else if(commandName == "chop.seqs")				{	command = new ChopSeqsCommand(optionString);				}
		else if(commandName == "clearcut")				{	command = new ClearcutCommand(optionString);				}
		else if(commandName == "catchall")				{	command = new CatchAllCommand(optionString);				}
		else if(commandName == "split.abund")			{	command = new SplitAbundCommand(optionString);				}
		else if(commandName == "cluster.split")			{	command = new ClusterSplitCommand(optionString);			}
		else if(commandName == "classify.otu")			{	command = new ClassifyOtuCommand(optionString);				}
		else if(commandName == "degap.seqs")			{	command = new DegapSeqsCommand(optionString);				}
		else if(commandName == "get.relabund")			{	command = new GetRelAbundCommand(optionString);				}
		else if(commandName == "sens.spec")				{	command = new SensSpecCommand(optionString);				}
		else if(commandName == "seq.error")				{	command = new SeqErrorCommand(optionString);				}
		else if(commandName == "sffinfo")				{	command = new SffInfoCommand(optionString);					}
		else if(commandName == "normalize.shared")		{	command = new NormalizeSharedCommand(optionString);			}
		else											{	command = new NoCommand(optionString);						}

		return command;
	}
	catch(exception& e) {
		m->errorOut(e, "CommandFactory", "getCommand");
		exit(1);
	}
}
/***********************************************************/
//This function is used to interrupt a command
Command* CommandFactory::getCommand(){
	try {
		delete command;   //delete the old command

		string s = "";
	    command = new NoCommand(s);
	
		return command;
	}
	catch(exception& e) {
		m->errorOut(e, "CommandFactory", "getCommand");
		exit(1);
	}
}
/***********************************************************************/
bool CommandFactory::isValidCommand(string command) {
	try {	
	
		//is the command in the map
		if ((commands.find(command)) != (commands.end())) {
			return true;
		}else{
			m->mothurOut(command + " is not a valid command in Mothur.  Valid commands are ");
			for (it = commands.begin(); it != commands.end(); it++) {
				m->mothurOut(it->first + ", ");
			}
			m->mothurOutEndLine();
			return false;
		}
		
	}
	catch(exception& e) {
		m->errorOut(e, "CommandFactory", "isValidCommand");
		exit(1);
	}
}

/***********************************************************************/
void CommandFactory::printCommands(ostream& out) {
	try {	
		out << "Valid commands are: ";
		for (it = commands.begin(); it != commands.end(); it++) {
			out << it->first << ",";
		}
		out << endl;
	}
	catch(exception& e) {
		m->errorOut(e, "CommandFactory", "printCommands");
		exit(1);
	}
}
/***********************************************************************/




