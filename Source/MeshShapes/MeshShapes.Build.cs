using UnrealBuildTool;

public class MeshShapes : ModuleRules
{
	public MeshShapes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"MeshShapes/Public"
			});

		PrivateIncludePaths.AddRange(
			new string[] {
				"MeshShapes/Private",
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			    "RuntimeMeshComponent",
            });

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
                "RuntimeMeshComponent",
				"Slate",
				"SlateCore",
			});

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			});

	    if (Target.bBuildEditor == true)
	        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
    }
}