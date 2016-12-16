docker.image('jenkins-ubuntu-1604').inside {
	stage 'Clean before build'
	sh 'rm -rf .[^.] .??* *'

	stage 'Checkout'
	checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/muhkuh-sys/org.muhkuh.tools-hboot_image_compiler.git']]])

	stage 'Build'
	sh 'python mbs/mbs'

	stage 'Save Artifacts'
	archive 'targets/repository/org/muhkuh/tools/hboot_image_compiler/*/*.zip,targets/repository/org/muhkuh/tools/hboot_image_compiler/*/*.pom'

	stage 'Clean after build'
	sh 'rm -rf .[^.] .??* *'
}
