// Copyright Ramon Janousch. MIT License.

using UnrealBuildTool;
using System.Collections.Generic;

public class VersionControlEditorTarget : TargetRules
{
	public VersionControlEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "VersionControl" } );
	}
}
