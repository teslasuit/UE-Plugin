import os
import shutil

RELEASE_DIR_NAME = 'Unreal Engine Release'

def make_release_folder():
    if os.path.isdir(RELEASE_DIR_NAME):
        shutil.rmtree(RELEASE_DIR_NAME)
    os.mkdir(RELEASE_DIR_NAME)

def prepare_plugin_to_release():
    plugin_dir = os.path.join(RELEASE_DIR_NAME, 'UE Plugin')
    shutil.copytree(os.path.join('Plugins'), plugin_dir)

    for folder in ['Binaries', 'Intermediate']:
        shutil.rmtree(os.path.join(plugin_dir, 'Teslasuit', folder))

def prepare_demo_project_to_release():
    demo_project_dir = os.path.join(RELEASE_DIR_NAME, 'UE Demo Project')
    
    for folder in ['Config', 'Content', 'Plugins', 'Source']:
        shutil.copytree(folder, os.path.join(demo_project_dir, folder))

    project_file = 'TeslasuitPlugin.uproject'
    shutil.copyfile(project_file, os.path.join(demo_project_dir, project_file))

    for folder in ['Binaries', 'Intermediate']:
        shutil.rmtree(os.path.join(demo_project_dir, 'Plugins', 'Teslasuit', folder))


if __name__ == '__main__':
    make_release_folder()
    prepare_plugin_to_release()
    prepare_demo_project_to_release()