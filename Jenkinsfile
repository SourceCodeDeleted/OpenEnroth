pipeline {
    agent any
    stages {
        stage('getting dependencies') {
            steps {
                 // Clean before build
                cleanWs()
                // We need to explicitly checkout from SCM here
                checkout scm
                echo "Building ${env.JOB_NAME}..."


                sh 'chmod +x buildscripts/dep_builder.sh'
                sh './buildscripts/dep_builder.sh'
            }
        }
        
        stage('Build') {
            steps {
                def workspace = WORKSPACE
                sh 'cd ${workspace}'
                sh 'echo "building..."'
                sh 'cmake -B build -S .'
                sh 'cmake --build build'
            }
        }
          post {
        // Clean after build
        always {
            cleanWs(cleanWhenNotBuilt: false,
                    deleteDirs: true,
                    disableDeferredWipeout: true,
                    notFailBuild: true,
                    patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                               [pattern: '.propsfile', type: 'EXCLUDE']])
        }
          }
        
        
    }
}
