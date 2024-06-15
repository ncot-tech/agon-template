#!/usr/bin/env python3

# This might turn into something later...

import questionary, os, json

# Get the current working directory
current_directory = os.getcwd()

# Get the parent directory of the current working directory
parent_directory = os.path.dirname(current_directory)

DEFAULT_CONFIG = {
    "project": {
        "name": "Test Project",
        "desc": "My Test Project",
        "dir" : ""
    },
    "emulator": {
        "dir": "../fab-agon-emulator",
        "bin": "fab-agon-emulator",
        "flags": "--scale 2000",
        "sdcard": "~/.agon-sdcard"
    },
    "hardware": {
        "sdcard": "/media/blah",
    }
}

def load_config(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)

def merge_with_defaults(config, default_config):
    for key in default_config:
        if key not in config:
            config[key] = default_config[key]
        elif isinstance(default_config[key], dict):
            merge_with_defaults(config[key], default_config[key])

def convert_to_lower_with_underscores(input_string):
    # Convert the string to lowercase
    lowercased_string = input_string.lower()
    
    # Replace spaces with underscores
    underscored_string = lowercased_string.replace(' ', '_')
    
    return underscored_string

def main():
    config = DEFAULT_CONFIG
    questionary.print("== Project Creation Tool ==", style="bold fg:yellow")

    if os.path.exists("project_config.json"):
        questionary.print("Found config file, loading contents", style="bold fg:yellow")
        config = load_config('project_config.json')
        merge_with_defaults(config, DEFAULT_CONFIG)      

    done = False
    while not done:
        project_name = questionary.text("Enter name of project", default=config["project"]["name"]).ask()
        project_name_lower = convert_to_lower_with_underscores(project_name)

        config["project"]["name"] = project_name

        proj_dir = questionary.path(
        "Where do you want to store your project?",
        default=config["project"]["dir"]
        ).ask()

        config["project"]["dir"] = proj_dir

        print (f"This will create a folder called {proj_dir}/{project_name_lower}")
        done = questionary.confirm("Is this OK?").ask()

if __name__ == "__main__":
    main()






    
questionary.password("What's your secret?").ask()


questionary.select(
    "What do you want to do?",
    choices=[
        "Order a pizza",
        "Make a reservation",
        "Ask for opening hours"
    ]).ask()
