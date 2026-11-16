all:
	echo "r-common"

clean:
	(cd c ; make clean)

push-all:
	r.gitlab-push.sh r-common
	r.github-push.sh r-common

push-tags:
	r.gitlab-push.sh r-common --tags
	r.github-push.sh r-common --tags
