// Copyright Ramon Janousch. MIT License.

using UnrealBuildTool;
using System.Collections.Generic;

public class VersionControlTarget : TargetRules
{
	public VersionControlTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "VersionControl" } );
	}
}
