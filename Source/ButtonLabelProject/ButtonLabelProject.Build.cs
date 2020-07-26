// Coypright Markus Ort - All Rights Reserved.

using UnrealBuildTool;

public class ButtonLabelProject : ModuleRules
{
	public ButtonLabelProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] 
			{ 
				"Core", 
				"CoreUObject",
				"Engine", 
				"InputCore",
				"UMG"
			});

		PrivateDependencyModuleNames.AddRange(
		new string[] 
			{ 
				"Slate", 
				"SlateCore" 
			});
		
	}
}
